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

auto GetCurTime() -> std::chrono::milliseconds {
    using namespace std::chrono;
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

void ScreenStrategy(const std::vector<Logger::Log> &logs) {
    std::for_each(logs.begin(), logs.end(), [](const auto &log) { std::cout << log; });
}

struct FStream {
    std::fstream f_;

    explicit FStream(const std::string &path = LOG_PATH) {
        f_.open(path + "-" + GetCurDate(), std::ios_base::out | std::ios_base::trunc);
    }

    ~FStream() {
        if (f_.is_open()) {
            f_.flush();
            f_.close();
        }
    }

    void WriteAll(const std::vector<Logger::Log> &logs) {
        std::for_each(logs.begin(), logs.end(), [this](auto &log) { f_ << log; });
        f_.flush();
    }
};

void FileStrategy(const std::vector<Logger::Log> &logs) {
    static FStream writer;
    writer.WriteAll(logs);
}

Logger::Logger(const std::function<void(const std::vector<Log> &)> &log_strategy) {
    log_strategy_func_ = log_strategy;
    last_flush_ = GetCurTime();
    log_writer_ = std::thread(&Logger::writing_log, this);
}

void Logger::push_log(tinynet::Logger::Log &&log) {
    using std::chrono::milliseconds;
    bool should_notify = false;
    {
        std::unique_lock<std::mutex> lock(mtx_);
        logs_.emplace_back(std::move(log));
        milliseconds msec = GetCurTime();
        if ((msec - last_flush_) > REFRESH_TIME || logs_.size() > MAX_LOG_QUEUE) {
            should_notify = true;
        }
    }
    if (should_notify) {
        cv_.notify_one();
    }
}

Logger &Logger::Instance() {
    static Logger logger{FileStrategy};
    return logger;
}

void Logger::LogMsg(tinynet::LogLevel log_level, const std::string &msg) noexcept {
    auto log = Logger::Log(log_level, msg);
    Instance().push_log(std::move(log));
}

void Logger::writing_log() {
    std::vector<Logger::Log> wv;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]() {
            return stop_ || logs_.size() > MAX_LOG_QUEUE || GetCurTime() - last_flush_ > REFRESH_TIME;
        });
        if (logs_.size()) {
            wv.swap(logs_);
            lock.unlock();
            log_strategy_func_(wv);
            last_flush_ = GetCurTime();
            wv.clear();
        }
        if (stop_) {
            return;
        }
    }
}

Logger::~Logger() {
    stop_ = true;
    cv_.notify_one();
    if (log_writer_.joinable()) {
        log_writer_.join();
    }
}

}