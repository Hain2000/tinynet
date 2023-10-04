//
// Created by Hain_official on 2023-10-04.
//
#include "Acceptor.h"
#include "EventLoop.h"
#include "ThreadPool.h"
#include <memory>
#include <unistd.h>
#include <atomic>
#include <future>
using namespace tinynet;

int main() {
    NetAddress local_host("127.0.0.1", 8888);
    ThreadPool pool;
    auto single_looper = std::make_unique<EventLoop>();
    std::vector<EventLoop *> raw_loopers = {single_looper.get()};
    auto acceptor = Acceptor(single_looper.get(), raw_loopers, local_host);
    assert(acceptor.GetAcceptorConnection()->GetFd() != -1);

    int client_num = 3;
    std::atomic<int> accept_trigger = 0;
    std::atomic<int> handle_trigger = 0;

    acceptor.SetAcceptCallBack([&](Connection *) { accept_trigger++; });
    acceptor.SetHandleCallBack([&](Connection *) { handle_trigger++; });

    const char *msg = "YYDS 114514 1919810( ^,^)";
    std::vector<std::future<void>> futs;
    for (int i = 0; i < client_num; i++) {
        auto fut = std::async(std::launch::async, [&]() {
            Socket client_sock;
            client_sock.Connect(local_host);
            CHECK(client_sock.GetFd() != -1);
            send(client_sock.GetFd(), msg, strlen(msg), 0);
        });
        futs.emplace_back(std::move(fut));
    }

    auto runner = std::async(std::launch::async, [&]() {
        single_looper->Loop();
    });

    sleep(2);
    single_looper->SetStop();
    CHECK(accept_trigger == client_num);
    CHECK(handle_trigger >= client_num);

    for (auto &f : futs) {
        f.wait();
    }
}