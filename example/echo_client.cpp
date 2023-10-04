//
// Created by Hain_official on 2023-10-04.
//
#include "TcpServer.h"

using namespace tinynet;
const int BUF_SIZE = 2048;

class EchoClient {
public:
    explicit EchoClient(NetAddress server_address) {
        auto client_socket = std::make_unique<Socket>();
        client_socket->Connect(server_address);
        client_connection = std::make_unique<Connection>(std::move(client_socket));
    }

    void Start() {
        char buf[BUF_SIZE + 1];
        memset(buf, 0, sizeof(buf));
        int fd = client_connection->GetFd();
        while (true) {
            auto actual_read = read(STDIN_FILENO, buf, BUF_SIZE);
            send(fd, buf, actual_read, 0);
            memset(buf, 0, sizeof(buf));
            auto actual_recv = recv(fd, buf, BUF_SIZE, 0);
            write(STDOUT_FILENO, buf, actual_recv);
            memset(buf, 0, sizeof(buf));
        }
    }

private:
    std::unique_ptr<Connection> client_connection;
};

int main() {
    NetAddress local_address("127.0.0.1", 8899);
    EchoClient echo_client(local_address);
    echo_client.Start();
}