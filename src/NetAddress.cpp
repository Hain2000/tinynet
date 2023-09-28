//
// Created by Hain_official on 2023-09-27.
//
#include "NetAddress.h"
namespace tinynet {

NetAddress::NetAddress() noexcept {
    memset(&addr_, 0, sizeof addr_);
    addr_len_ = sizeof(addr_);
}

NetAddress::NetAddress(const char *ip, uint16_t port, Protocol protocol) : protocol_(protocol) {
    memset(&addr_, 0, sizeof addr_);
    addr_len_ = sizeof(addr_);
    if (protocol == Protocol::Ipv4) {
        auto addr = reinterpret_cast<struct sockaddr_in *>(&addr_);
        addr->sin_family = AF_INET;
        inet_pton(AF_INET, ip, &addr->sin_addr.s_addr); // ip 转 数字
        addr->sin_port = htons(port);
    } else {
        auto addr = reinterpret_cast<struct sockaddr_in6 *>(&addr_);
        addr->sin6_family = AF_INET6;
        inet_pton(AF_INET6, ip, &addr->sin6_addr.s6_addr); // ip 转 数字
        addr->sin6_port = htons(port);
    }
}


auto NetAddress::GetProtocol() const noexcept -> Protocol {
    return protocol_;
}

auto NetAddress::YieldAddr() -> struct sockaddr * {
    return reinterpret_cast<struct sockaddr *>(&addr_);
};

auto NetAddress::YieldAddrLen() -> socklen_t * {
    return &addr_len_;
}

auto NetAddress::GetIp() const noexcept -> std::string {
    char ip_address[INET6_ADDRSTRLEN]; // ipv4和ipv6都放得下
    if (protocol_ == Protocol::Ipv4) {
        auto addr = reinterpret_cast<struct sockaddr_in *>(&addr_);
        inet_ntop(AF_INET, &addr->sin_addr, ip_address, INET_ADDRSTRLEN);
    } else {
        auto addr = reinterpret_cast<struct sockaddr_in6 *>(&addr_);
        inet_ntop(AF_INET6, &addr->sin6_addr, ip_address, INET6_ADDRSTRLEN);
    }
    return std::string(ip_address);
}

auto NetAddress::GetPort() const noexcept -> uint16_t {
    uint16_t port;
    if (protocol_ == Protocol::Ipv4) {
        auto addr = reinterpret_cast<struct sockaddr_in *>(&addr_);
        port = ntohs(addr->sin_port);
    } else {
        auto addr = reinterpret_cast<struct sockaddr_in6 *>(&addr_);
        port = ntohs(addr->sin6_port);
    }
    return port;
}

auto NetAddress::ToString() const noexcept -> std::string {
    return GetIp() + "@" + std::to_string(GetPort());
}


}