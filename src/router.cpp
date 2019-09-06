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
#include <string.h>
#include <fstream>
#include <sstream>

void Router::submit(std::string &request, int &socket)
{
    std::string first_line = request.substr(0, request.find("\r\n"));
    std::string method = first_line.substr(0, request.find(" "));
    std::string path = first_line.substr(first_line.find(" ") + 2, first_line.rfind("HTTP/1.1") - 6);

    if (path == "")
    {
        path = "index.html";
    }

    if (method != "GET")
    {
        std::string message = "HTTP/1.1 404 NOT FOUND\r\nContent-Type: text/plain\r\nContent-Length: 23\r\n\r\nMethod not supported!\r\n";
        write(socket, message.c_str(), message.length());
    }
    else
    {
        serve(path, socket);
    }
}

void Router::serve(std::string &path, int &socket)
{
    std::ifstream file;
    std::string current_line;
    std::ostringstream content;
    unsigned int file_size;

    file.open("./content/" + path);
    if (file.is_open())
    {
        while (!file.eof())
        {
            std::getline(file, current_line);
            file_size += current_line.length();
            content << current_line;
        }
        std::ostringstream response = generate_header(file_size);
        response << content.str();
        write(socket, response.str().c_str(), response.str().length());
    } else {
        std::cerr << "Could not find file" << std::endl;
        std::string message = "HTTP/1.1 404 NOT FOUND\r\nContent-Type: text/html\r\nContent-Length: 30\r\n\r\n<h1>404: Page Not Found</h1>\r\n";
        write(socket, message.c_str(), message.length());
    }
}

std::ostringstream Router::generate_header(unsigned int size)
{
    std::ostringstream header;
    header << "HTTP/1.1 200 OK\r\n";
    header << "Content-Type: text/html\r\n";
    header << "Content-Length: " << size << "\r\n";
    header << "\r\n";
    return header;
}