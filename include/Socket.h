//
// Created by Hain_official on 2023-09-14.
//

#ifndef TINYNET_SOCKET_H
#define TINYNET_SOCKET_H

#include "utils.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>

struct tcp_info;

namespace tinynet {



//Socket类，创建的Socket对象默认都是非阻塞的
//职责：
//1、提供fd操作的相关API
//2、管理fd的生命周期
//其中有引用计数，若某一fd没人用了就会close
class Socket {
public:

    explicit Socket(int sockfd, std::string ip = "127.0.0.1", int port = 8888)
        : sockfd_(sockfd)
        , p_ref_(new int(1))
        , port_(port)
        , ip_(std::move(ip)) {
        
        if (sockfd > 0) {
            SetNonBolckSocket();
        }
        
    }

    Socket()
        : sockfd_(::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP))
        , p_ref_(new int(1))
        , port_(8888)
        , ip_("127.0.0.1") {
        
    }

    Socket(const Socket &other_sock)
        : sockfd_(other_sock.sockfd_) {
        *(other_sock.p_ref_) += 1;
        p_ref_ = other_sock.p_ref_;
        ip_ = other_sock.ip_;
        port_ = other_sock.port_;
    }

    Socket(Socket &&other_sock)
        : sockfd_(other_sock.sockfd_) {
        *(other_sock.p_ref_) += 1;
        p_ref_ = other_sock.p_ref_;
        ip_ = std::move(other_sock.ip_);
        port_ = other_sock.port_;
    }

    Socket &operator=(const Socket& other_sock) = delete;

    ~Socket();

    //返回当前Socket的fd
    int fd() const { return sockfd_; }

    //返回当前Socket是否可用
    bool IsUseful() { return sockfd_ >= 0; }

    // 绑定ip和port到当前Socket
    int bind(int port);

    //开始监听当前Socket
    int listen();

    // 阻塞接收一个连接，返回一个新连接的Socket
    Socket accept();

    // 从socket中读数据
    ssize_t read(void* buf, size_t count);

    // 往socket中写数据
    ssize_t send(const void* buf, size_t count);

    // 获取当前套接字的目标ip
    std::string ip() { return ip_; }

    // 获取当前套接字的目标port
    int port() { return port_; }

    // 获取套接字的选项,成功则返回true，反之，返回false
    bool GetSocketOpt(struct tcp_info*) const;

    // 获取套接字的选项的字符串,成功则返回true，反之，返回false
    bool GetSocketOptString(char* buf, int len) const;

    // 获取套接字的选项的字符串
    std::string GetSocketOptString() const;

    // 关闭套接字的写操作
    int ShutdownWrite();

    // 设置是否开启Nagle算法减少需要传输的数据包，若开启延时可能会增加
    int SetTcpNoDelay(bool on);

    // 设置是否地址重用
    int SetReuseAddr(bool on);

    // 设置是否端口重用
    int SetReusePort(bool on);

    // 设置是否使用心跳检测
    int SetKeepAlive(bool on);

    // 设置socket为非阻塞的
    int SetNonBolckSocket();

    // 设置socket为阻塞的
    int SetBlockSocket();

    //void SetNoSigPipe();


private:
    
    const int sockfd_;
    int *p_ref_; // 引用计数
    int port_;
    std::string ip_;
};


}


#endif //TINYNET_SOCKET_H
