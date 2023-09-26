//
// Created by Hain_official on 2023-09-26.
//
#include "Logger.h"
#include <iostream>
#include <filesystem>


// using namespace tinynet;

auto GetCurTime() -> std::chrono::milliseconds {
    using namespace std::chrono;
    // 系统时间指的是 1970年1月1日0时0分0秒起至现在的总秒数
    // 这里time_since_epoch()的返回值是类型是时间长度（duration类型），即从纪元起点到now对应时间点间的时间长度。
    // 时间长度类型可以通过count()转化为数值类型，方便进一步在其他代码中使用
    // 时间转换
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

auto GetCurDate() -> std::string {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream stream;
    stream << std::put_time(&tm, "%d%b%Y");
    return stream.str();
}

int main() {
    std::cout << GetCurDate() << std::endl;
    std::cout << GetCurTime().count() << std::endl;
    LOG_WARNING("YYDS")
    LOG_ERROR("AABB")
    LOG_INFO("114514")
    LOG_FATAL("1919810")
}