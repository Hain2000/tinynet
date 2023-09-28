//
// Created by Hain_official on 2023-09-28.
//
#include "NetAddress.h"
#include "Socket.h"
#include "Logger.h"
#include <iostream>
#include <cassert>
#include <fcntl.h>
using namespace tinynet;

void f1() {
    NetAddress local_host("127.0.0.1", 8888);
    Socket server_sock;
    server_sock.Bind(local_host);
    server_sock.Listen();
    NetAddress client_address;
    int clnt_sockfd = server_sock.Accept(client_address);
    while (true) {
        char buf[1024];     //定义缓冲区
        bzero(&buf, sizeof(buf));       //清空缓冲区
        ssize_t read_bytes = read(clnt_sockfd, buf, sizeof(buf)); //从客户端socket读到缓冲区，返回已读数据大小
        if(read_bytes > 0){
            for (int i = 0; i < read_bytes; i++) {
                buf[i] = toupper(buf[i]);
            }
            printf("message from client fd %d: %s\n", clnt_sockfd, buf);
            write(clnt_sockfd, buf, sizeof(buf));           //将相同的数据写回到客户端
        } else if(read_bytes == 0){             //read返回0，表示EOF
            printf("client fd %d disconnected\n", clnt_sockfd);
            close(clnt_sockfd);
            break;
        } else if(read_bytes == -1){        //read返回-1，表示发生错误，按照上文方法进行错误处理
            close(clnt_sockfd);
        }
    }
}

int main(int argc, char **argv) {
    NetAddress local_host("127.0.0.1", 8888);
    Socket server_sock;
    server_sock.Bind(local_host);
    server_sock.Listen();

    if (argv[1] == "o") {
        int fd = server_sock.GetFd();
        Socket o_sock(114);
        server_sock = std::move(o_sock);
        assert(server_sock.GetFd() == 114);
        assert(o_sock.GetFd() == fd);

        Socket second_sock = std::move(o_sock);
        assert(second_sock.GetFd() == fd);
        assert(o_sock.GetFd() == -1);

    } else if (argv[1] == "c") {
        NetAddress client_address;
        std::thread t([&]() {
            Socket client_sock;
            client_sock.Connect(local_host);
        });
        t.detach();
        assert(server_sock.Accept(client_address) != -1);
    } else if (argv[1] == "n") {
        Socket sock;
        sock.Bind(local_host);
        assert((sock.GetAttrs() & O_NONBLOCK) == 0);
        sock.SetNonBlockSocket();
        assert((sock.GetAttrs() & O_NONBLOCK) != 0);
    } else if (argv[1] == "null") {

    }
}