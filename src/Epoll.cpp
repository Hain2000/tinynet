//
// Created by Hain_official on 2023-09-29.
//
#include "Epoll.h"
#include <unistd.h>
#include <cassert>
#include <cstring>
#include "Logger.h"
#include <Connection.h>

namespace tinynet {

Epoll::Epoll(uint16_t epoll_events_size) : epoll_events_size_(epoll_events_size) {
    epoll_fd_ = epoll_create1(0);
    if (epoll_fd_ == -1) {
        perror("Epoll : epoll_create1() err");
        exit(EXIT_FAILURE);
    }
    events_ = new struct epoll_event[epoll_events_size];
    memset(events_, 0, epoll_events_size * sizeof(struct epoll_event));
}

Epoll::~Epoll() {
    if (epoll_fd_ != -1) {
        close(epoll_fd_);
        delete[] events_;
        epoll_fd_ = -1;
    }
}

auto Epoll::GetEventsSize() const noexcept -> uint16_t {
    return epoll_events_size_;
}

void Epoll::AddConnection(tinynet::Connection *conn) {
    assert(conn->GetFd() != -1 && "AddConnection() fd invalid");
    struct epoll_event event;
    memset(&event, 0, sizeof(struct epoll_event));
    event.data.ptr = conn;
    event.events = conn->GetEvents();
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, conn->GetFd(), &event) == -1) {
        perror("Epoll: AddConnection() epoll_ctl add error");
        exit(EXIT_FAILURE);
    }
}

auto Epoll::Poll(int timeout) -> std::vector<Connection *> {
    std::vector<Connection *> res;
    int nfds = epoll_wait(epoll_fd_, events_, epoll_events_size_, timeout);
    if (nfds == -1) {
        perror("EPoll: Poll() err");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nfds; i++) {
        Connection *res_conn = reinterpret_cast<Connection *>(events_[i].data.ptr);
        res_conn->SetRevents(events_[i].events);
        res.emplace_back(res_conn);
    }
    return res;
}


}