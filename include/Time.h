//
// Created by Hain_official on 2023-09-15.
//

#ifndef TINYNET_TIME_H
#define TINYNET_TIME_H
#include <time.h>
#include <cstdint>

namespace tinynet {

const char days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Time {
public:
    Time(int64_t time_val = 0) : time_val_(time_val) {}

    Time(const Time &time) { time_val_ = time.time_val_; }
    Time(const Time &&time) { time_val_ = time.time_val_; }

    Time &operator=(const Time &time) {
        time_val_ = time.time_val_;
        return *this;
    }

    ~Time();

    static Time Now();
    static time_t NowSec();

    // 根据距离1970-01-01 00:00:00的秒数和与秒数所属时区的时差计算当前时区的时间
    static void ToLocalTime(time_t second, long timezone_second, struct tm *tm_time);

    // 到现在的时间
    struct timespec TimeIntervalFromNow();

    int64_t GetTimeVal() const { return time_val_; }

    bool operator<(const Time &rhs) const { return time_val_ < rhs.time_val_; }
    bool operator<=(const Time &rhs) const { return time_val_ <= rhs.time_val_; }
    bool operator>(const Time &rhs) const { return time_val_ > rhs.time_val_; }
    bool operator>=(const Time &rhs) const { return time_val_ >= rhs.time_val_; }
    bool operator==(const Time &rhs) const { return time_val_ == rhs.time_val_; }

private:
    int64_t time_val_; // 微秒级
};

}


#endif //TINYNET_TIME_H
