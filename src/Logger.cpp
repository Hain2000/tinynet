//
// Created by Hain_official on 2023-09-15.
//

#include "Logger.h"
#include <filesystem>
#include <fstream>
#include <iostream>
namespace tinynet {

const char *level_name_[] = {"INFO: ", "ERROR: ", "FATAL: ", "WARNING: "};

Logger::Log::Log(tinynet::LogLevel log_level, const std::string &msg) noexcept {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "[%d %b %Y %H:%M:%S]") << tinynet::level_name_[log_level] << msg << std::endl;
    record_ = oss.str();
}

Logger &Logger::Instance() {
    static Logger logger{};
    return logger;
}

void Logger::LogMsg(tinynet::LogLevel log_level, const std::string &msg) noexcept {
    auto log = Logger::Log(log_level, msg);
    std::cout << log.record_;
}

}