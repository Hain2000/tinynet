//
// Created by Hain_official on 2023-09-14.
//

#include "Socket.h"
#include "Logger.h"
#include <assert.h>
#include <stdexcept>
#include <fcntl.h>
namespace tinynet {

static constexpr int BACK_LOG = 128;

Socket::Socket(int fd) noexcept : fd_(fd) {}

Socket::Socket(tinynet::Socket &&other) noexcept {
    fd_ = other.fd_;
    other.fd_ = -1;
}

auto Socket::operator=(tinynet::Socket &&other) noexcept -> Socket & {
    if (fd_ != -1) {
        close(fd_);
    }
    std::swap(fd_, other.fd_);
    return *this;
}

auto Socket::GetFd() const noexcept -> int {
    return fd_;
}

void Socket::SetReusable() {
    assert(fd_ != -1 && "SetReusable() fd invalid");
    int yes = 1;
    // SO_REUSEADDR 当服务端出现timewait状态的链接时，确保server能够重启成功。
    // SO_REUSEPORT 允许多个线程(进程)创建独立的socket，多个绑定相同ip:port，进行独立的listen()和accept()，以提高接受能力
    if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1 ||
        setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(yes)) == -1) {
        LOG_ERROR("Socket: SetReusable() err");
        throw std::logic_error("Socket: SetReusable() err");
    }
}

void Socket::new_fd(tinynet::Protocol protocol) {
    if (protocol == Protocol::Ipv4) {
        fd_ = socket(AF_INET, SOCK_STREAM, 0);
    } else {
        fd_ = socket(AF_INET6, SOCK_STREAM, 0);
    }
    if (fd_ == -1) {
        LOG_ERROR("Socket: new_fd() err");
        throw std::logic_error("Socket: new_fd() err");
    }
}

void Socket::Bind(tinynet::NetAddress &server_addr, bool set_reusable) {
    if (fd_ == -1) {
        new_fd(server_addr.GetProtocol());
    }
    if (set_reusable) {
        SetReusable();
    }
    if (bind(fd_, server_addr.YieldAddr(), *server_addr.YieldAddrLen()) == -1) {
        LOG_ERROR("Socket: Bind() err");
        throw std::logic_error("Socket: Bind() err");
    }
}

void Socket::Listen() {
    assert(fd_ != -1 && "Listen() fd invalid");
    if (listen(fd_, BACK_LOG) == -1) {
        LOG_ERROR("Listen() fd invalid");
        throw std::logic_error("Listen() fd invalid");
    }
}

auto Socket::Accept(tinynet::NetAddress &client_addr) -> int {
    assert(fd_ != -1 && "Accept() fd invalid");
    int client_fd = accept(fd_, client_addr.YieldAddr(), client_addr.YieldAddrLen());
    if (client_fd == -1) {
        // 高压下，accept可能会失败，服务器并不会故障
        LOG_WARNING("Socket: Accept() err");
    }
    return client_fd;
}

void Socket::SetNonBlockSocket() {
    assert(fd_ != -1 && "SetNonBlockSocket() fd invalid");
    if (fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL) | O_NONBLOCK) == -1) {
        LOG_ERROR("Socket: SetNonBlockSocket() err");
        throw std::logic_error("Socket: SetNonBlockSocket() err");
    }
}

auto Socket::GetAttrs() -> int {
    assert(fd_ != -1 && "GetAttrs() fd invalid");
    return fcntl(fd_, F_GETFL);
}

void Socket::Connect(NetAddress &server_addr) {
    if (fd_ == -1) {
        new_fd(server_addr.GetProtocol());
    }
    if (connect(fd_, server_addr.YieldAddr(), *server_addr.YieldAddrLen()) == -1) {
        LOG_ERROR("Socket: Connect() err");
        throw std::logic_error("Socket: Connect() err");
    }
}

Socket::~Socket() {
    if (fd_ != -1) {
        close(fd_);
        fd_ = -1;
    }
}


}
