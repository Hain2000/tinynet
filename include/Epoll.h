//
// Created by Hain_official on 2023-09-29.
//

#ifndef TINYNET_EPOLL_H
#define TINYNET_EPOLL_H

#include <sys/epoll.h>
#include <vector>

namespace tinynet {
static constexpr int DEFAULT_EPOLL_EVENTS_SIZE = 1024;
class Connection;
class Epoll {
public:
    explicit Epoll(uint16_t epoll_events_size = DEFAULT_EPOLL_EVENTS_SIZE);

    ~Epoll();

    void AddConnection(Connection *conn);

    auto Poll(int timeout = -1) -> std::vector<Connection *>;

    auto GetEventsSize() const noexcept -> uint16_t;
private:
    int epoll_fd_{-1};
    uint16_t epoll_events_size_;
    struct epoll_event *events_;
};



}



#endif //TINYNET_EPOLL_H
