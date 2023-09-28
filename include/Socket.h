//
// Created by Hain_official on 2023-09-14.
//

#ifndef TINYNET_SOCKET_H
#define TINYNET_SOCKET_H

#include "utils.h"

#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include "NetAddress.h"


namespace tinynet {

class Socket {
public:

    Socket() noexcept = default;
    explicit Socket(int fd) noexcept;

    Socket(Socket &&other) noexcept;
    auto operator=(Socket &&other) noexcept -> Socket &;

    ~Socket();

    auto GetFd() const noexcept -> int;

    void Connect(NetAddress &server_addr);

    void Bind(NetAddress &server_addr, bool set_reusable = true);

    void Listen();

    auto Accept(NetAddress &client_addr) -> int;

    void SetReusable();

    // 设置socket为非阻塞的
    void SetNonBlockSocket();

    auto GetAttrs() -> int;


private:
    void new_fd(Protocol protocol);
    int fd_{-1}; // 初始化
};


}


#endif //TINYNET_SOCKET_H
