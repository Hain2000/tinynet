//
// Created by Hain_official on 2023-09-29.
//

#ifndef TINYNET_CONNECTION_H
#define TINYNET_CONNECTION_H
#include <memory>
#include <Socket.h>
#include <functional>
namespace tinynet {
// 相当于muduo Channel + Connection

class EventLoop;

class Connection {
public:

    Connection(std::unique_ptr<Socket> socket);
    ~Connection() = default;

    auto GetFd() const noexcept ->  int;
    auto GetSocket() noexcept -> Socket *;

    void SetEvents(uint32_t events);
    auto GetEvents() const noexcept -> uint32_t;
    void SetRevents(uint32_t revents);
    auto GetRevents() const noexcept -> uint32_t;

    void SetCallBack(const std::function<void(Connection *)> &callback);
    auto GetCallBack() noexcept -> std::function<void()>;

private:
    EventLoop *loop_{nullptr};
    std::unique_ptr<Socket> socket_;
    uint32_t events_{0};
    uint32_t revents_{0};
    std::function<void()> callback_{nullptr};
};

}


#endif //TINYNET_CONNECTION_H
