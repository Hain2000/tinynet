//
// Created by Hain_official on 2023-09-26.
//
#include "Logger.h"
#include <iostream>
using namespace tinynet;

int main() {
    std::cout << "Hello world" << "\n";
    LOG_INFO("YYDS");
    LOG_ERROR("114514");
    LOG_FATAL("1919810");
    LOG_WARNING("MEOW");
}