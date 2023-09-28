//
// Created by Hain_official on 2023-09-15.
//

#ifndef TINYNET_LOGGER_H
#define TINYNET_LOGGER_H
#include <ctime>
#include <string>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#define LOG_INFO(x) tinynet::Logger::LogMsg(tinynet::LogLevel::INFO, (x));
#define LOG_WARNING(x) tinynet::Logger::LogMsg(tinynet::LogLevel::WARNING, (x));
#define LOG_ERROR(x) tinynet::Logger::LogMsg(tinynet::LogLevel::ERROR, (x));
#define LOG_FATAL(x) tinynet::Logger::LogMsg(tinynet::LogLevel::FATAL, (x));

namespace tinynet {

const std::string LOG_PATH = std::string("TinyNetLog");
constexpr int MAX_LOG_QUEUE = 1000;
constexpr std::chrono::duration REFRESH_TIME = std::chrono::microseconds(3000);

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
    explicit Logger(const std::function<void(const std::vector<Log> &logs)> &log_strategy);

    ~Logger();

    void writing_log();
    void push_log(Log &&log);

    std::function<void(const std::vector<Log> &)> log_strategy_func_;
    std::vector<Log> logs_;
    std::atomic<bool> stop_{false};
    std::mutex mtx_;
    std::thread log_writer_;
    std::condition_variable cv_;
    std::chrono::microseconds last_flush_;
};


}

#endif //TINYNET_LOGGER_H
