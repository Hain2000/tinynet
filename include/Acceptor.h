//
// Created by Hain_official on 2023-10-04.
//

#ifndef TINYNET_ACCEPTOR_H
#define TINYNET_ACCEPTOR_H
#include "NetAddress.h"
#include "Connection.h"
#include "EventLoop.h"
#include <functional>

namespace tinynet {


class Acceptor {
public:
    Acceptor(EventLoop *listener, std::vector<EventLoop *> loopers, NetAddress server_address);

    ~Acceptor() = default;

    void BaseAcceptCallBack(Connection *server_conn);
    void BaseHandleCallBack(Connection *client_conn);


    void SetAcceptCallBack(std::function<void(Connection *)> accept_callback);
    auto GetAcceptCallBack() const noexcept -> std::function<void(Connection *)>;

    void SetHandleCallBack(std::function<void(Connection *)> handle_callback);
    auto GetHandleCallBack() const noexcept -> std::function<void(Connection *)>;

    auto GetAcceptorConnection() noexcept -> Connection *;


private:
    void next_cur_idx();

    std::vector<EventLoop *> loopers_;
    std::unique_ptr<Connection> accept_conn_;
    std::function<void(Connection *)> accept_callback_{};
    std::function<void(Connection *)> handle_callback_{};
    int cur_idx{0};
};


}




#endif //TINYNET_ACCEPTOR_H
