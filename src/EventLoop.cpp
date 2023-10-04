//
// Created by Hain_official on 2023-09-29.
//
#include "EventLoop.h"
#include "Epoll.h"
#include "Connection.h"
namespace tinynet {

EventLoop::EventLoop(uint64_t timer_expiration)
    : epoll_(std::make_unique<Epoll>())
    , timer_expiration_(timer_expiration) {
    if (timer_expiration != 0) {
        use_timer_ = true;
        epoll_->AddConnection(timer_.GetTimerConnection());
    }
}

void EventLoop::Loop() {
    while (!stop_) {
        auto conns = epoll_->Poll(TIMEOUT);
        Connection *timer_conn = nullptr;

        for (auto &x : conns) {
            if (x == timer_.GetTimerConnection()) {
                timer_conn = x; // 存最后一个
                continue;
            }
            x->GetCallBack()();
        }

        if (timer_conn != nullptr) {
            timer_conn->GetCallBack()();
        }
    }
}

void EventLoop::AddAcceptor(tinynet::Connection *new_conn) {
    std::unique_lock<std::mutex> lock(mtx_);
    epoll_->AddConnection(new_conn);
}

void EventLoop::AddConnection(std::unique_ptr<Connection> new_conn) {
    std::unique_lock<std::mutex> lock(mtx_);
    epoll_->AddConnection(new_conn.get());
    int fd = new_conn->GetFd();
    connections_.insert({fd, std::move(new_conn)});
    if (use_timer_) {
        auto single_timer = timer_.AddSingleTimer(timer_expiration_, [this, fd]() {
            LOG_INFO("client fd=" + std::to_string(fd) + "has expired and will be kicked out");
            DeleteConnection(fd);
        });
        single_timers_.insert({fd, single_timer});
    }
}

auto EventLoop::RefreshConnection(int fd) noexcept -> bool {
    if (!use_timer_) {
        return false;
    }
    std::unique_lock<std::mutex> lock(mtx_);
    auto it = single_timers_.find(fd);
    if (use_timer_ && it != single_timers_.end()) {
        auto new_timer = timer_.RefreshSingleTimer(it->second, timer_expiration_);
        if (new_timer != nullptr) {
            single_timers_.insert({fd, new_timer});
        }
        return true;
    }
    return false;
}

auto EventLoop::DeleteConnection(int fd) noexcept -> bool {
    std::unique_lock<std::mutex> lock(mtx_);
    auto it = connections_.find(fd);
    if (it == connections_.end()) {
        return false;
    }
    connections_.erase(it);
    if (use_timer_) {
        auto single_timer_it = single_timers_.find(fd);
        if (single_timer_it != single_timers_.end()) {
            timer_.RemoveSingleTimer(single_timer_it->second);
            single_timers_.erase(single_timer_it);
        } else {
            LOG_ERROR("EventLoop: DeleteConnection() the fd " + std::to_string(fd) + " not in single_timers_");
        }
    }
    return true;
}

void EventLoop::SetStop() noexcept {
    stop_ = true;
}

}