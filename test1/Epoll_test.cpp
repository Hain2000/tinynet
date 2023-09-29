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
    NetAddress local_host("127.0.0.1", 8888);
    Socket server_sock;

    server_sock.Bind(local_host);
    server_sock.Listen();
    assert(server_sock.GetFd() != -1);

    int client_num = 3;
    Epoll poller(client_num);
    assert(poller.GetEventsSize() == client_num);

    std::vector<std::thread> threads;
    for (int i = 0; i < client_num; i++) {
        threads.emplace_back([&]() {
            auto client_socket = Socket();
            client_socket.Connect(local_host);
            char msg[] = "Hello from client!";
            send(client_socket.GetFd(), msg, strlen(msg), 0);
            sleep(2);
        });
    }

    std::vector<std::shared_ptr<Connection>> client_conns;
    for (int i = 0; i < client_num; i++) {
        NetAddress client_address;
        auto client_sock = std::make_unique<Socket>(server_sock.Accept(client_address));
        CHECK(client_sock->GetFd() != -1);
        client_conns.push_back(std::make_shared<Connection>(std::move(client_sock)));
        client_conns[i]->SetEvents(EPOLLIN);
    }

    for (int i = 0; i < client_num; i++) {
        poller.AddConnection(client_conns[i].get());
    }
    sleep(1);
    auto ready_conns = poller.Poll();
    CHECK(ready_conns.size() == client_num);

    for (int i = 0; i < client_num; i++) {
        threads[i].join();
    }


}