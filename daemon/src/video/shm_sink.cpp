/*
 *  Copyright (C) 2012 Savoir-Faire Linux Inc.
 *  Author: Tristan Matthews <tristan.matthews@savoirfairelinux.com>
 *
 *  Portions derived from GStreamer:
 *  Copyright (C) <2009> Collabora Ltd
 *  @author: Olivier Crete <olivier.crete@collabora.co.uk
 *  Copyright (C) <2009> Nokia Inc
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Additional permission under GNU GPL version 3 section 7:
 *
 *  If you modify this program, or any covered work, by linking or
 *  combining it with the OpenSSL project's OpenSSL library (or a
 *  modified version of that library), containing parts covered by the
 *  terms of the OpenSSL or SSLeay licenses, Savoir-Faire Linux Inc.
 *  grants you additional permission to convey the resulting work.
 *  Corresponding Source for a non-source form of such a combination
 *  shall include the source code for the parts of OpenSSL used as well
 *  as that of the covered work.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "shm_sink.h"
#include "shm_header.h"
#include "logger.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <cstdio>
#include <sstream>
#include <unistd.h>
#include <cerrno>
#include <cstring>

SHMSink::SHMSink(const std::string &shm_name) :
    shm_name_(shm_name),
    fd_(-1),
    shm_area_(static_cast<SHMHeader*>(MAP_FAILED)),
    shm_area_len_(0),
    opened_name_(),
    perms_(S_IRUSR | S_IWUSR | S_IRGRP)
    {}

SHMSink::~SHMSink()
{
    stop();
}

bool
SHMSink::start()
{
    if (fd_ != -1) {
        ERROR("fd must be -1");
        return false;
    }

    const int flags = O_RDWR | O_CREAT | O_TRUNC | O_EXCL;
    if (not shm_name_.empty()) {
        fd_ = shm_open(shm_name_.c_str(), flags, perms_);
        if (fd_ < 0) {
            ERROR("could not open shm area \"%s\", shm_open failed:%s", shm_name_.c_str(), strerror(errno));
            perror(strerror(errno));
            return false;
        }
    } else {
        for (int i = 0; fd_ < 0; ++i) {
            std::ostringstream name;
            name << PACKAGE_NAME << "_shm_" << getpid() << "_" << i;
            shm_name_ = name.str();
            fd_ = shm_open(shm_name_.c_str(), flags, perms_);
            if (fd_ < 0 and errno != EEXIST) {
                ERROR("%s", strerror(errno));
                return false;
            }
        }
    }

    DEBUG("Using name %s", shm_name_.c_str());
    opened_name_ = shm_name_;

    shm_area_len_ = sizeof(SHMHeader);

    if (ftruncate(fd_, shm_area_len_)) {
        ERROR("Could not make shm area large enough for header");
        perror(strerror(errno));
        return false;
    }

    shm_area_ = static_cast<SHMHeader*>(mmap(NULL, shm_area_len_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0));

    if (shm_area_ == MAP_FAILED) {
        ERROR("Could not map shm area, mmap failed");
        return false;
    }

    memset(shm_area_, 0, shm_area_len_);
    if (sem_init(&shm_area_->notification, 1, 0) != 0) {
        ERROR("sem_init: notification initialization failed");
        return false;
    }
    if (sem_init(&shm_area_->mutex, 1, 1) != 0) {
        ERROR("sem_init: mutex initialization failed");
        return false;
    }
    return true;
}

bool
SHMSink::stop()
{
    if (fd_ >= 0)
        close(fd_);
    fd_ = -1;

    if (not opened_name_.empty()) {
        shm_unlink(opened_name_.c_str());
        opened_name_ = "";
    }

    if (shm_area_ != MAP_FAILED)
        munmap(shm_area_, shm_area_len_);
    shm_area_len_ = 0;
    shm_area_ = static_cast<SHMHeader*>(MAP_FAILED);

    return true;
}

bool
SHMSink::resize_area(size_t desired_length)
{
    if (desired_length < shm_area_len_)
        return true;

    shm_unlock();

    if (munmap(shm_area_, shm_area_len_)) {
        ERROR("Could not unmap shared area");
        perror(strerror(errno));
        return false;
    }

    if (ftruncate(fd_, desired_length)) {
        ERROR("Could not resize shared area");
        perror(strerror(errno));
        return false;
    }

    shm_area_ = static_cast<SHMHeader*>(mmap(NULL, desired_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0));
    shm_area_len_ = desired_length;

    if (shm_area_ == MAP_FAILED) {
        shm_area_ = 0;
        ERROR("Could not remap shared area");
        return false;
    }

    shm_lock();
    return true;
}

void SHMSink::render(const std::vector<unsigned char> &data)
{
    shm_lock();

    if (!resize_area(sizeof(SHMHeader) + data.size()))
        return;

    memcpy(shm_area_->data, &(*data.begin()), data.size());
    shm_area_->buffer_size = data.size();
    shm_area_->buffer_gen++;
    sem_post(&shm_area_->notification);
    shm_unlock();
}

// Note: this doesn't depend on VideoReceiveThread's implementation since it's forward declared.
void SHMSink::render_callback(sfl_video::VideoReceiveThread * const th, const Callback &callback, size_t bytes)
{
    shm_lock();

    if (!resize_area(sizeof(SHMHeader) + bytes)) {
        ERROR("Could not resize area");
        return;
    }

    callback(th, static_cast<void*>(shm_area_->data));
    shm_area_->buffer_size = bytes;
    shm_area_->buffer_gen++;
    sem_post(&shm_area_->notification);
    shm_unlock();
}

void SHMSink::shm_lock()
{
    sem_wait(&shm_area_->mutex);
}

void SHMSink::shm_unlock()
{
    sem_post(&shm_area_->mutex);
}