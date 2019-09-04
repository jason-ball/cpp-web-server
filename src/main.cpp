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

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <csignal>

void sig_int_handler(int number);

const uint16_t PORT = 8080u;
int SERVER_RUNNING = 1;
const unsigned int MAX_CONNECTIONS = 10;
const unsigned int BUFFER_SIZE = 30000;
const char *TEST_MESSAGE = "HTTP/1.1 200 OK\r\n" \
                           "Content-Type: text/plain\r\n" \
                           "Content-Length: 12\r\n" \
                           "\r\n" \
                           "Hello World!";
int server_fd, new_socket;

int main()
{
    signal(SIGINT, sig_int_handler);
    struct sockaddr_in address{};
    size_t addr_len;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error creating server socket");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;
    memset(&address.sin_zero, 0, sizeof(address.sin_zero));
    addr_len = sizeof(address);

    if (bind(server_fd, (const sockaddr *) &address, sizeof(address)))
    {
        perror("Could not bind");
        return 2;
    }

    if (listen(server_fd, MAX_CONNECTIONS) < 0)
    {
        perror("Could not listen");
        return 3;
    }

    while(SERVER_RUNNING)
    {
        std::cout << "Waiting for a connection...\n" << std::endl;

        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addr_len)) < 0)
        {
            perror("Error accepting");
            return 4;
        }

        char buffer[BUFFER_SIZE] = {0};
        read(new_socket, buffer, BUFFER_SIZE);
        std::cout << "-------BEGIN HTTP REQUEST-------" << std::endl << buffer << std::endl << "--------END HTTP REQUEST--------" << std::endl;
        write(new_socket, TEST_MESSAGE, strlen(TEST_MESSAGE));
        close(new_socket);
    }


    return 0;
}

void sig_int_handler(int number)
{
    std::cout << "\nShutting down server..." << std::endl;
    SERVER_RUNNING = 0;
    close(server_fd);
    exit(number);
}
