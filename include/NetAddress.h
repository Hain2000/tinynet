//
// Created by Hain_official on 2023-09-27.
//

#ifndef TINYNET_NETADDRESS_H
#define TINYNET_NETADDRESS_H

#include <arpa/inet.h>

#include <cstring>
#include <iostream>
#include <string.h>

namespace tinynet {

enum class Protocol {
    Ipv4,
    Ipv6
};

class NetAddress {
public:
    NetAddress() noexcept;

    NetAddress(const char *ip, uint16_t port, Protocol protocol = Protocol::Ipv4);
    ~NetAddress() = default;

    auto GetProtocol() const noexcept -> Protocol;

    auto YieldAddr() -> struct sockaddr *;

    auto YieldAddrLen() -> socklen_t *;

    auto GetIp() const noexcept -> std::string;

    auto GetPort() const noexcept -> uint16_t;

    auto ToString() const noexcept -> std::string;

private:
    Protocol protocol_{Protocol::Ipv4};
    mutable struct sockaddr_storage addr_{}; // 128字节的通用地址
    socklen_t addr_len_;
};


}

#endif //TINYNET_NETADDRESS_H
