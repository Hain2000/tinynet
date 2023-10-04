//
// Created by Hain_official on 2023-10-04.
//
#include "Acceptor.h"

namespace tinynet {

Acceptor::Acceptor(tinynet::EventLoop *listener, std::vector<EventLoop *> loopers, tinynet::NetAddress server_address)
    : loopers_(std::move(loopers)) {
    auto acceptor_sock = std::make_unique<Socket>();
    acceptor_sock->Bind(server_address, true);
    acceptor_sock->Listen();
    accept_conn_ = std::make_unique<Connection>(std::move(acceptor_sock));
    accept_conn_->SetEvents(EPOLLIN);
    accept_conn_->SetLooper(listener);
    listener->AddAcceptor(accept_conn_.get());
    SetAcceptCallBack([](Connection *) {});
    SetHandleCallBack([](Connection *) {});
}

void Acceptor::BaseAcceptCallBack(tinynet::Connection *server_conn) {
    NetAddress client_addr;
    int accept_fd = server_conn->GetSocket()->Accept(client_addr);
    if (accept_fd == -1) {
        return;
    }
    auto client_sock = std::make_unique<Socket>(accept_fd);
    client_sock->SetNonBlockSocket();
    auto client_conn = std::make_unique<Connection>(std::move(client_sock));
    client_conn->SetEvents(EPOLLIN | EPOLLET);
    client_conn->SetCallBack(GetHandleCallBack());
    int idx = 0;
    for (int i = 0; i < loopers_.size(); i++) {
        if (loopers_[i]->ConnectionsSize() < loopers_[idx]->ConnectionsSize()) {
            idx = i;
        }
    }
    LOG_INFO("new client fd = " + std::to_string(client_conn->GetFd()) + "maps to reactor " + std::to_string(idx));
    client_conn->SetLooper(loopers_[idx]);
    loopers_[idx]->AddConnection(std::move(client_conn));
}

void Acceptor::BaseHandleCallBack(Connection *client_conn) {
    int fd = client_conn->GetFd();
    if (client_conn->GetLooper()) {
        client_conn->GetLooper()->RefreshConnection(fd);
    }
}

void Acceptor::SetAcceptCallBack(std::function<void(Connection *)> accept_callback) {
    accept_callback_ = std::move(accept_callback);
    accept_conn_->SetCallBack([this](auto &&f) {
        BaseAcceptCallBack(std::forward<decltype(f)>(f));
        accept_callback_(std::forward<decltype(f)>(f));
    });
}

void Acceptor::SetHandleCallBack(std::function<void(Connection *)> handle_callback) {
    handle_callback_ = [this, callback = std::move(handle_callback)](auto &&f) {
        BaseHandleCallBack(std::forward<decltype(f)>(f));
        callback(std::forward<decltype(f)>(f));
    };
}

auto Acceptor::GetAcceptCallBack() const noexcept -> std::function<void(Connection *)> {
    return accept_callback_;
}

auto Acceptor::GetHandleCallBack() const noexcept -> std::function<void(Connection *)> {
    return handle_callback_;
}

auto Acceptor::GetAcceptorConnection() noexcept -> Connection * {
    return accept_conn_.get();
}

}