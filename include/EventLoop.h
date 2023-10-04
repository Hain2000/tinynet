//
// Created by Hain_official on 2023-09-29.
//

#ifndef TINYNET_EVENTLOOP_H
#define TINYNET_EVENTLOOP_H
#include <memory>
#include <mutex>
#include <map>
#include "Timer.h"

namespace tinynet {

static constexpr int TIMEOUT = 3000;

static constexpr uint64_t INACTIVE_TIMEOUT = 3000;

class Epoll;
class Connection;

class EventLoop {
public:
    EventLoop(uint64_t timer_expiration);

    void Loop();

    void AddAcceptor(Connection *new_conn);

    void AddConnection(std::unique_ptr<Connection> new_conn);

    auto RefreshConnection(int fd) noexcept -> bool;

    auto DeleteConnection(int fd) noexcept -> bool;

    void SetStop() noexcept;
private:
    std::mutex mtx_;
    std::unique_ptr<Epoll> epoll_;
    bool stop_{false};
    std::map<int, std::unique_ptr<Connection>> connections_;
    Timer timer_{};
    std::map<int, SingleTimer *> single_timers_;
    bool use_timer_{false};
    uint64_t timer_expiration_{0};
};

}


#endif //TINYNET_EVENTLOOP_H
