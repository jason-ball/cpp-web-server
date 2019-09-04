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

#include "../include/router.h"
#include <iostream>

void Router::submit(std::string &request)
{
    std::string first_line = request.substr(0 , request.find("\r\n"));
    std::string method = first_line.substr(0, request.find(" "));
    std::string path = first_line.substr(first_line.find(" ") + 2, first_line.rfind("HTTP/1.1") - 6);
    /* std::cout << "First Line: " << first_line << std::endl;
    std::cout << "Method: " << method << std::endl;
    std::cout << "Path: " << path << std::endl; */
}