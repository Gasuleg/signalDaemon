/************************************************************************************
 *   Copyright (C) 2012 by Savoir-Faire Linux                                       *
 *   Author : Emmanuel Lepage Vallee <emmanuel.lepage@savoirfairelinux.com>         *
 *                                                                                  *
 *   This library is free software; you can redistribute it and/or                  *
 *   modify it under the terms of the GNU Lesser General Public                     *
 *   License as published by the Free Software Foundation; either                   *
 *   version 2.1 of the License, or (at your option) any later version.             *
 *                                                                                  *
 *   This library is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of                 *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              *
 *   Lesser General Public License for more details.                                *
 *                                                                                  *
 *   You should have received a copy of the GNU Lesser General Public               *
 *   License along with this library; if not, write to the Free Software            *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA *
 ***********************************************************************************/

#ifndef DLG_VIDEO_H
#define DLG_VIDEO_H

#include <QWidget>

#include "ui_dlgvideobase.h"

class VideoDevice;

///@class DlgVideo video preferences for sflphone
class DlgVideo : public QWidget, public Ui_DlgVideoBase
{
Q_OBJECT
public:
   //Constructor
   DlgVideo(QWidget *parent = 0);

   //Destructor
   ~DlgVideo();

private:
   VideoDevice* m_pDevice;

};

#endif