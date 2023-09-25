cmake_minimum_required(VERSION 3.16)
project(tinynet CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)

add_executable(tinynet
        include/options.h
        include/utils.h
        main.cpp
        include/ThreadPool.h
        include/nocopyable.h
        src/ThreadPool.cpp
        include/Socket.h
        src/Socket.cpp
        include/Logger.h
        src/Logger.cpp
        src/Time.cpp
        include/Time.h)
