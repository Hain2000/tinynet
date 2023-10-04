//
// Created by Hain_official on 2023-10-04.
//

#ifndef TINYNET_TCPSERVER_H
#define TINYNET_TCPSERVER_H
#include "Acceptor.h"
#include "EventLoop.h"
#include "ThreadPool.h"
#include "NetAddress.h"
#include "Connection.h"
#include <memory>
#include <utility>
#include <stdexcept>
#include <errno.h>
#include <algorithm>
namespace tinynet {

class TcpServer {
public:
    TcpServer(NetAddress server_address, int concurrency = static_cast<int>(std::thread::hardware_concurrency()) - 1) {
        pool_ = std::make_unique<ThreadPool>(concurrency);
        listener_ = std::make_unique<EventLoop>();
        for (size_t i = 0; i < pool_->GetSize(); i++) {
            loopers_.emplace_back(std::make_unique<EventLoop>());
        }
        for (auto &reactor : loopers_) {
            pool_->Emplace([&reactor] { reactor->Loop(); });
        }
        std::vector<EventLoop *> raw_loopers;
        raw_loopers.reserve(loopers_.size());
        std::transform(loopers_.begin(), loopers_.end(), std::back_inserter(raw_loopers), [](auto &uni_p) {
            return uni_p.get();
        });
        acceptor_ = std::make_unique<Acceptor>(listener_.get(), raw_loopers, server_address);
    }

    auto OnAccept(std::function<void(Connection *)> on_accept) -> TcpServer & {
        acceptor_->SetAcceptCallBack(std::move(on_accept));
        return *this;
    }

    auto OnHandle(std::function<void(Connection *)> on_handle) -> TcpServer & {
        acceptor_->SetHandleCallBack(std::move(on_handle));
        on_handle_set_ = true;
        return *this;
    }

    void Start() {
        if (!on_handle_set_) {
            throw std::logic_error("Please specify OnHandle callback function before starts");
        }
        listener_->Loop();
    }

private:
    bool on_handle_set_{false};
    std::unique_ptr<Acceptor> acceptor_;
    std::vector<std::unique_ptr<EventLoop>> loopers_;
    std::unique_ptr<ThreadPool> pool_;
    std::unique_ptr<EventLoop> listener_;
};

}




#endif //TINYNET_TCPSERVER_H
