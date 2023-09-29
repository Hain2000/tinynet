//
// Created by Hain_official on 2023-09-29.
//

#ifndef TINYNET_EVENTLOOP_H
#define TINYNET_EVENTLOOP_H
#include <memory>
#include <mutex>
namespace tinynet {
class Epoll;
class Connection;

class EventLoop {
public:
    EventLoop();

    void Loop();

    void AddAcceptor(Connection *new_conn);

    void SetStop() noexcept;
private:
    std::mutex mtx_;
    std::unique_ptr<Epoll> epoll_;
    bool stop_{false};
};

}


#endif //TINYNET_EVENTLOOP_H
