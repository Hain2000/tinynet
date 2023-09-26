//
// Created by Hain_official on 2023-09-15.
//

#ifndef TINYNET_LOGGER_H
#define TINYNET_LOGGER_H
#include <ctime>
#include <string>

#define LOG_INFO(x) tinynet::Logger::LogMsg(tinynet::LogLevel::INFO, (x));
#define LOG_WARNING(x) tinynet::Logger::LogMsg(tinynet::LogLevel::WARNING, (x));
#define LOG_ERROR(x) tinynet::Logger::LogMsg(tinynet::LogLevel::ERROR, (x));
#define LOG_FATAL(x) tinynet::Logger::LogMsg(tinynet::LogLevel::FATAL, (x));

namespace tinynet {


    // 日志级别  INFO  ERROR  FATAL
enum LogLevel {
    INFO,     // 普通信息
    ERROR,    // 错误信息
    FATAL,    // core信息
    WARNING,    // 警告信息
};

class Logger {
public:

    static void LogMsg(LogLevel log_level, const std::string &msg) noexcept;

    struct Log {
        std::string record_;

        Log(LogLevel log_level, const std::string &msg) noexcept;

        friend std::ostream &operator<<(std::ostream &os, const Log &log) {
            os << log.record_;
            return os;
        }
    };

    static Logger &Instance();

private:

};


}

#endif //TINYNET_LOGGER_H
