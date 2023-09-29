//
// Created by Hain_official on 2023-09-29.
//
#include "Epoll.h"
#include "Connection.h"
#include "NetAddress.h"
#include "Socket.h"
#include <cassert>
#include <iostream>
#include <atomic>
#include <memory>
#include <numeric>
#include <thread>
#include <vector>
using namespace tinynet;

void CHECK(bool ok) {
    if (ok) {
        printf("OK!\n");
    } else {
        printf("ERROR!, %d\n", __LINE__);
    }
}

int main() {
    NetAddress local_host("127.0.0.1", 20080);
    auto server_sock = std::make_unique<Socket>();
    server_sock->Bind(local_host);
    server_sock->Listen();
    Connection server_conn(std::move(server_sock));
    assert(server_conn.GetSocket() != nullptr);

    server_conn.SetEvents(EPOLL_CTL_ADD | EPOLLET);
    CHECK((server_conn.GetEvents() & EPOLL_CTL_ADD));
    CHECK((server_conn.GetEvents() & EPOLLET));
    server_conn.SetRevents(EPOLLIN);
    CHECK((server_conn.GetRevents() & EPOLLIN));

    server_conn.SetCallBack([](Connection *) -> void {});
    int i = 0;
    server_conn.SetCallBack([&target = i](Connection *) -> void { target += 1; });
    server_conn.GetCallBack()();
    CHECK(i == 1);
}