cmake_minimum_required(VERSION 3.16)
project(tinynet CXX)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pthread")


include_directories(.)
include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(echo_server ${SOURCES} example/echo_server.cpp)

add_executable(echo_client ${SOURCES} example/echo_client.cpp)
