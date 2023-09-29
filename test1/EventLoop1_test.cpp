//
// Created by Hain_official on 2023-09-29.
//
#include "Epoll.h"
#include "EventLoop.h"
#include "NetAddress.h"
#include "Socket.h"
#include "Logger.h"
#include "Connection.h"
#include <cassert>
#include <iostream>
#include <numeric>
using namespace tinynet;

void CHECK(bool ok, int line = 0) {
    if (ok) {
        printf("OK!\n");
    } else {
        printf("ERROR!: %d\n", line);
    }
}

int main() {
    NetAddress local_host("127.0.0.1", 8888);
    Socket server_sock;
    server_sock.Bind(local_host);
    server_sock.Listen();
    assert(server_sock.GetFd() != -1);

    EventLoop looper;

    int client_num = 3;
    std::vector<std::thread> threads;
    for (int i = 0; i < client_num; i++) {
        threads.emplace_back([&host = local_host]() {
            auto client_socket = Socket();
            client_socket.Connect(host);
            sleep(1);
        });
    }

    std::vector<int> reach(client_num, 0);
    for (int i = 0; i < client_num; i++) {
        NetAddress client_address;
        auto client_sock = std::make_unique<Socket>(server_sock.Accept(client_address));
        CHECK(client_sock->GetFd() != -1);
        client_sock->SetNonBlockSocket();
        auto client_conn = std::make_unique<Connection>(std::move(client_sock));
        client_conn->SetEvents(EPOLLIN);
        client_conn->SetCallBack([&reach = reach, index = i](Connection *conn) { reach[index] = 2; });
        // client_conn->GetCallBack()();
        looper.AddAcceptor(client_conn.get());
    }

    std::thread runner([&]() { looper.Loop(); });
    sleep(2);
    looper.SetStop();

    CHECK(std::accumulate(reach.begin(), reach.end(), 0) == 2 * client_num, __LINE__);
    std::cout << std::accumulate(reach.begin(), reach.end(), 0) << "\n";
    runner.join();
    for (int i = 0; i < client_num; i++) {
        threads[i].join();
    }
}
