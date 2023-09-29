//
// Created by Hain_official on 2023-09-29.
//

#include "Connection.h"

namespace tinynet {

Connection::Connection(std::unique_ptr<Socket> socket) : socket_(std::move(socket)) {}

auto Connection::GetFd() const noexcept -> int {
    return socket_->GetFd();
}

auto Connection::GetSocket() noexcept -> Socket * {
    return socket_.get();
}

void Connection::SetEvents(uint32_t events) {
    events_ = events;
}

auto Connection::GetEvents() const noexcept -> uint32_t {
    return events_;
}

void Connection::SetRevents(uint32_t revents) {
    revents_ = revents;
}

auto Connection::GetRevents() const noexcept -> uint32_t {
    return revents_;
}

void Connection::SetCallBack(const std::function<void(Connection *)> &callback) {
    callback_ = [callback, this] { callback(this); };
}

auto Connection::GetCallBack() noexcept -> std::function<void()> {
    return callback_;
}

}