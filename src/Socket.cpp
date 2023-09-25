//
// Created by Hain_official on 2023-09-14.
//
#include <cstring>
#include "Socket.h"

using namespace tinynet;

Socket::~Socket() {
    (*p_ref_)--;
    if (!(*p_ref_) && IsUseful()) {
        if (::close(sockfd_) < 0) {
            // log
        } else {
            // log
        }
        delete p_ref_;
    }
}

int Socket::bind(int port) {
    port_ = port;
    struct sockaddr_in serv;
    std::memset(&serv, 0, sizeof(struct sockaddr_in));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    int res = ::bind(sockfd_, (struct sockaddr *) &serv, sizeof(serv));
    if (res < 0) {
        // log
    }
    return res;
}

int Socket::listen() {
    int res = ::listen(sockfd_, options::kBackLog);
    if (res < 0) {
        // log
    }
    return res;
}

Socket Socket::accept() {
    int connfd = -1;
    struct sockaddr_in client;
    socklen_t client_len = sizeof(client);
    connfd = ::accept(sockfd_, (struct sockaddr *)&client, &client_len);
    if (connfd < 0) {
        //
        return Socket(connfd);
    }


}