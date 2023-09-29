cmake_minimum_required(VERSION 3.16)
project(tinynet CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(.)
include_directories(include)

add_executable(tinynet
        src/NetAddress.cpp
        include/NetAddress.h
        src/Socket.cpp
        include/Socket.h
        src/Socket.cpp
        include/Logger.h
        src/Logger.cpp
        include/Connection.h
        src/Connection.cpp
        include/Epoll.h
        src/Epoll.cpp
        include/EventLoop.h
        src/EventLoop.cpp
        test1/EventLoop1_test.cpp
)
