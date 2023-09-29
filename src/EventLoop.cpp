//
// Created by Hain_official on 2023-09-29.
//
#include "EventLoop.h"
#include "Epoll.h"
#include "Connection.h"
namespace tinynet {

EventLoop::EventLoop() : epoll_(std::make_unique<Epoll>()) {}

void EventLoop::Loop() {
    if (stop_) {
        printf("AA\n");
    } else {
        printf("BB\n");
    }
    while (!stop_) {
        printf("CC\n");
        auto conns = epoll_->Poll();
        printf("conns size: %lu\n", conns.size());
        for (auto &x : conns) {
            x->GetCallBack()();
            printf("YYDS\n");
        }
    }
}

void EventLoop::AddAcceptor(tinynet::Connection *new_conn) {
    std::lock_guard<std::mutex> lock(mtx_);
    epoll_->AddConnection(new_conn);
}

void EventLoop::SetStop() noexcept {
    stop_ = true;
}

}