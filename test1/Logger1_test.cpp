//
// Created by Hain_official on 2023-09-26.
//
#include "Logger.h"
#include <iostream>
#include <filesystem>


// using namespace tinynet;

auto GetCurTime() -> std::chrono::seconds {
    using namespace std::chrono;
    // 系统时间指的是 1970年1月1日0时0分0秒起至现在的总秒数
    // 这里time_since_epoch()的返回值是类型是时间长度（duration类型），即从纪元起点到now对应时间点间的时间长度。
    // 时间长度类型可以通过count()转化为数值类型，方便进一步在其他代码中使用
    // 时间转换
    return duration_cast<seconds>(system_clock::now().time_since_epoch());
}

auto GetCurDate() -> std::string {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream stream;
    stream << std::put_time(&tm, "%d%b%Y");
    return stream.str();
}

int main() {
    auto t1 =  GetCurTime().count();
    for (int i = 0; i <= 10000000; i++) {
        LOG_INFO("HAIN" + std::to_string(i) + "hain");
    }
    std::cout << GetCurTime().count() - t1 << "\n";
}