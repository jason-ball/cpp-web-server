cmake_minimum_required(VERSION 3.0)
project(cpp-web-server)
set(CMAKE_CXX_STANDARD 14)
include_directories(include/)

set(SOURCE_FILES src/main.cpp src/router.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(cpp-web-server ${SOURCE_FILES})
