// cpp-web-server - A simple C++ Web Server
// Copyright (C) 2019 Jason Ball

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef CPP_WEB_SERVER_ROUTER_H
#define CPP_WEB_SERVER_ROUTER_H

#include <string>

class Router {
    public:
        void submit(std::string &request, int &socket);
};

#endif