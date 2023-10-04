//
// Created by Hain_official on 2023-10-04.
//
#include "TcpServer.h"

using namespace tinynet;

int main() {
    NetAddress local_address("127.0.0.1", 8899);
    TcpServer echo_server(local_address);
    echo_server.OnHandle([&](Connection *client_conn) {
        int from_fd = client_conn->GetFd();
        auto [read, exit] = client_conn->Recv();
        if (exit) {
            client_conn->GetLooper()->DeleteConnection(from_fd);
            return;
        }
        if (read) {
            std::string s = std::move(client_conn->ReadAsString());
            for (auto &c : s) {
                c = toupper(c);
            }
            println(client_conn->ReadAsString());
            client_conn->WriteToWriteBuffer(s);
            client_conn->Send();
            client_conn->ClearReadBuffer();
        }
    });
    echo_server.Start();
}