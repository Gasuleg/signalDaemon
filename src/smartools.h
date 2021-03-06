/*
 *  Copyright (C) 2004-2016 Savoir-faire Linux Inc.
 *
 *  Author: Olivier Grégoire <olivier.gregoire@savoirfairelinux.com>
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
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */
 #ifndef SMARTOOLS_H_
 #define SMARTOOLS_H_

 #include <chrono>

 #include "threadloop.h"
 #include "manager.h"
 #include <thread>
 #include <iostream>
 #include <cstring>
 #include <unistd.h>
 #include <getopt.h>

 namespace ring {
 class Smartools{
    public:
      Smartools(int refreshTimeMs);
      void start();
      void stop();

    private:
      int refreshTime;
      void process();
      const std::string *cpu;
      ThreadLoop loop_; // as to be last member
  };
} //ring namespace
#endif //smartools.h
