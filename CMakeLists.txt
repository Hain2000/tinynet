cmake_minimum_required(VERSION 3.16)
project(tinynet CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(.)
include_directories(include)

add_executable(tinynet
        include/ThreadPool.h
        include/nocopyable.h
        src/ThreadPool.cpp
        test1/ThreadPool_test.cpp
)
