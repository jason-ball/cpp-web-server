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
#include <unistd.h>
#include <string>

const char *TEST_MESSAGE = "HTTP/1.1 200 OK\r\n" \
                           "Content-Type: text/plain\r\n" \
                           "Content-Length: 12\r\n" \
                           "\r\n" \
                           "Hello World!";

void Router::submit(std::string &request, int &socket)
{
    std::string first_line = request.substr(0 , request.find("\r\n"));
    std::string method = first_line.substr(0, request.find(" "));
    std::string path = first_line.substr(first_line.find(" ") + 2, first_line.rfind("HTTP/1.1") - 6);

    if (method != "GET")
    {
        std::string message = "HTTP/1.1 404 NOT FOUND\r\nContent-Type: text/plain\r\nContent-Length: 23\r\n\r\nMethod not supported!\r\n";
        write(socket, message.c_str(), message.length());
    } else {
        write(socket, TEST_MESSAGE, strlen(TEST_MESSAGE));
    }
    
}