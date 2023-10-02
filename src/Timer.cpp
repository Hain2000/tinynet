//
// Created by Hain_official on 2023-09-29.
//
#include "Timer.h"
namespace tinynet {



Timer::Timer() : timer_fd_(timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC)) {
    if (timer_fd_ < 0) {
        LOG_FATAL("Timer() : timerfd_create() fails");
        exit(EXIT_FAILURE);
    }
    timer_conn_ = std::make_unique<Connection>(std::make_unique<Socket>(timer_fd_));
    timer_conn_->SetEvents(EPOLLIN | EPOLLET);
    timer_conn_->SetCallBack(std::bind(&Timer::handle_read, this));
}

auto Timer::GetTimerConnection() -> Connection * {
    return timer_conn_.get();
}

auto Timer::GetTimerFd() -> int {
    return timer_fd_;
}

auto Timer::AddSingleTimer(uint64_t expire_from_now, const std::function<void()> &callback)
noexcept -> SingleTimer * {
    std::unique_lock<std::mutex> lock(mtx_);
    auto new_timer = std::make_unique<SingleTimer>(expire_from_now, callback);
    auto raw_new_timer = new_timer.get(); // 记录指针，否则会有bugn
    timer_queue_.emplace(raw_new_timer, std::move(new_timer));
    assert(new_timer.get() == 0);
    uint64_t new_next_expire = NextExpireTime();
    if (new_next_expire != next_expire_) {
        next_expire_ = new_next_expire;
        ResetTimerFd(timer_fd_, FromNowTimeSpec(new_next_expire));
    }
    return raw_new_timer;
}

auto Timer::RemoveSingleTimer(SingleTimer *single_timer) noexcept -> bool {
    std::unique_lock<std::mutex> lock(mtx_);
    auto it = timer_queue_.begin();
    if (it != timer_queue_.end()) {
        timer_queue_.erase(it);
        auto new_next_expire = NextExpireTime();
        if (new_next_expire != next_expire_) {
            next_expire_ = new_next_expire;
            ResetTimerFd(timer_fd_, FromNowTimeSpec(new_next_expire));
        }
        return true;
    }
    return false;
}

auto Timer::RefreshSingleTimer(SingleTimer *single_timer, uint64_t expire_from_now)
noexcept -> SingleTimer * {
    std::unique_lock<std::mutex> lock(mtx_);
    auto it = timer_queue_.find(single_timer);
    if (it == timer_queue_.end()) {
        return nullptr;
    }
    auto new_timer = std::make_unique<SingleTimer>(expire_from_now, it->first->GetCallBack());
    auto raw_new_timer = new_timer.get();
    timer_queue_.erase(it);
    timer_queue_.emplace(raw_new_timer, std::move(new_timer));
    uint64_t new_next_expire = NextExpireTime();
    if (new_next_expire != next_expire_) {
        next_expire_ = new_next_expire;
        ResetTimerFd(timer_fd_, FromNowTimeSpec(new_next_expire));
    }
    return raw_new_timer;
}

auto Timer::NextExpireTime() const noexcept -> uint64_t {
    if (timer_queue_.empty()) {
        return 0;
    }
    return timer_queue_.begin()->first->WhenExpire();
}

auto Timer::TimerCount() const noexcept -> size_t {
    return timer_queue_.size();
}

auto Timer::PruneExpiredTimer() noexcept -> std::vector<std::unique_ptr<SingleTimer>> {
    std::unique_lock<std::mutex> lock(mtx_);
    std::vector<std::unique_ptr<SingleTimer>> expired;
    auto it = timer_queue_.begin();
    for (; it != timer_queue_.end(); it++) {
        if (!it->first->Expired()) {
            break;
        }
    }
    for (auto pre_it = timer_queue_.begin(); pre_it != it; pre_it++) {
        expired.emplace_back(std::move(pre_it->second));
    }
    timer_queue_.erase(timer_queue_.begin(), it);
    uint64_t new_next_expire = NextExpireTime();
    if (new_next_expire != next_expire_) {
        next_expire_ = new_next_expire;
        ResetTimerFd(timer_fd_, FromNowTimeSpec(new_next_expire));
    }
    return expired;
}

void Timer::handle_read() {
    uint64_t expired_size;
    ssize_t n = read(timer_fd_, &expired_size, sizeof(expired_size));
    if (n != sizeof(expired_size)) {
        LOG_ERROR("Timer: handle_read() read() err");
    }
    auto expired_timer = PruneExpiredTimer();
    for (const auto &single_expired : expired_timer) {
        single_expired->Run();
    }
}


}