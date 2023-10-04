//
// Created by Hain_official on 2023-09-29.
//
#include "Epoll.h"
#include "Connection.h"
#include "NetAddress.h"
#include "Socket.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <numeric>
#include <thread>
#include "utils.h"
using namespace tinynet;


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

    println("Buffer Test");
    const char *client_message = "hello from client";
    const char *server_message = "hello from server";
    std::thread client_thread([&]() {
        auto client_sock = std::make_unique<Socket>();
        client_sock->Connect(local_host);
        Connection client_conn(std::move(client_sock));

        client_conn.WriteToWriteBuffer(client_message);
        CHECK(client_conn.GetWriteBufferSize() == strlen(client_message));
        client_conn.Send();

        sleep(1);

        auto [read, exit] = client_conn.Recv();
        CHECK((read == strlen(server_message) && exit));
        CHECK(client_conn.ReadAsString() == std::string(server_message));
    });
    sleep(1);
    client_thread.detach();
    NetAddress client_address;
    auto connected_sock = std::make_unique<Socket>(server_conn.GetSocket()->Accept(client_address));
    connected_sock->SetNonBlockSocket();
    CHECK(connected_sock->GetFd() != -1);
    Connection connected_conn(std::move(connected_sock));
    sleep(1);
    auto [read, exit] = connected_conn.Recv();
    CHECK((read == strlen(client_message) && !exit));
    CHECK(connected_conn.GetReadBufferSize() == strlen(client_message));
    connected_conn.WriteToWriteBuffer(server_message);
    connected_conn.Send();
    sleep(1);
}