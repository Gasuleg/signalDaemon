/*
 *  Copyright (C) 2011 Savoir-Faire Linux Inc.
 *  Author: Rafaël Carré <rafael.carre@savoirfairelinux.com>
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

#include <iostream>
#include <iterator>
#include <vector>
#include <string>

#include "video_v4l2_list.h"

int main()
{
    using namespace sfl_video;
    using namespace std;

    VideoV4l2ListThread worker;
    vector<string> devs(worker.getDeviceList());

    for (size_t i = 0; i < devs.size(); ++i) {
        const string &dev = devs[i];
        cout << dev << endl;

        vector<string> channels(worker.getChannelList(dev));
        for (size_t i = 0; i < channels.size(); ++i) {
            const string &chan = channels[i];
            cout << '\t' << chan << endl;

            vector<string> sizes = worker.getSizeList(dev, chan);
            for (size_t i = 0; i < sizes.size(); ++i) {
                const string &size(sizes[i]);
                cout << "\t\t" << size << endl;
                vector<string> rates(worker.getRateList(dev, chan, size));
                copy(rates.begin(), rates.end(), ostream_iterator<string>(cout, "\t\t\t"));
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}