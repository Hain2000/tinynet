//
// Created by Hain_official on 2023-09-29.
//

#ifndef TINYNET_TIMER_H
#define TINYNET_TIMER_H
#include <sys/timerfd.h>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <unistd.h>
#include <chrono>
#include <vector>
#include <string.h>
#include <Logger.h>
#include "Connection.h"
#include "Socket.h"
#include "Epoll.h"

namespace tinynet {

static constexpr int MILLS_IN_SECOND = 1000;
static constexpr int NANOS_IN_MILL = 1000 * 1000;

static uint64_t NowSinceEpoch() { // 毫秒
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
}

static uint64_t FromNow(uint64_t timestamp) noexcept {
    auto now = NowSinceEpoch();
    return (timestamp >= now) ? (timestamp - now) : 0;
}

static struct timespec FromNowTimeSpec(uint64_t timestamp) {
    auto from_now_mills = FromNow(timestamp);
    struct timespec ts;
    ts.tv_sec = static_cast<time_t>(from_now_mills / MILLS_IN_SECOND);
    ts.tv_nsec = static_cast<int64_t>((from_now_mills % MILLS_IN_SECOND) * NANOS_IN_MILL);
    return ts;
}

static void ResetTimerFd(int timer_fd, struct timespec ts) {
    struct itimerspec new_value;
    struct itimerspec old_value;
    memset(&new_value, 0, sizeof(new_value));
    memset(&old_value, 0, sizeof(old_value));
    new_value.it_value = ts;
    int res = timerfd_settime(timer_fd, 0, &new_value, &old_value);
    if (res < 0) {
        LOG_ERROR("ResetTimerFd(): timerfd_settime fails");
    }
}

class SingleTimer {
public:
    SingleTimer(uint64_t expire_from_now, std::function<void()> callback) noexcept
            : expire_time_(NowSinceEpoch() + expire_from_now), callback_(std::move(callback)) {}

    auto WhenExpire() const noexcept -> uint64_t {
        return expire_time_;
    }

    auto Expired() const noexcept -> bool {
        return NowSinceEpoch() >= expire_time_;
    }

    auto GetCallBack() const noexcept -> std::function<void()> {
        return callback_;
    }

    void Run() noexcept {
        if (callback_) {
            callback_();
        }
    }

private:
    uint64_t expire_time_;
    std::function<void()> callback_{nullptr};
};

class Socket;
class Connection;

class Timer {
public:

    Timer();
    ~Timer() = default;

    auto GetTimerConnection() -> Connection *;

    auto GetTimerFd() -> int;

    auto AddSingleTimer(uint64_t expire_from_now, const std::function<void()> &callback) noexcept -> SingleTimer *;

    auto RemoveSingleTimer(SingleTimer *single_timer) noexcept -> bool;

    auto RefreshSingleTimer(SingleTimer *single_timer, uint64_t expire_from_now) noexcept -> SingleTimer *;

    auto NextExpireTime() const noexcept -> uint64_t ;

    auto PruneExpiredTimer() noexcept -> std::vector<std::unique_ptr<SingleTimer>>;

    auto TimerCount() const noexcept -> size_t;

private:

    struct Comparator {
        auto operator()(const SingleTimer *lhs, const SingleTimer *rhs) const noexcept -> bool {
            return lhs->WhenExpire() < rhs->WhenExpire();
        }
    };

    void handle_read();

    int timer_fd_;
    uint64_t next_expire_{0};
    mutable std::mutex mtx_;
    std::unique_ptr<Connection> timer_conn_;
    std::map<SingleTimer *, std::unique_ptr<SingleTimer>, Comparator> timer_queue_;
};
}
#endif //TINYNET_TIMER_H
