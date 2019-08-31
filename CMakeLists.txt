cmake_minimum_required(VERSION 3.0)
project(cpp-web-server)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp)

add_executable(cpp-web-server ${SOURCE_FILES})
