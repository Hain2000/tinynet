//
// Created by Hain_official on 2023-09-14.
//

#ifndef TINYNET_THREADPOOL_H
#define TINYNET_THREADPOOL_H
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <queue>
#include <vector>
#include <memory>
#include "nocopyable.h"
#include <>
namespace tinynet {

class thread_pool : nocopyable {
public:
    thread_pool();
    ~thread_pool();

    void Emplace(std::function<void()> &&);

private:
    int usable_q_;
    bool stop_;

    std::vector<std::thread> workers_;
    // 双任务队列，一条一直在被外界放任务，一条一直在被线程消费执行任务
    std::queue<std::function<void()>> tasks_[2];

    std::mutex thread_mtx_;  // ִ线程用锁
    std::mutex q_mtx_;       // 切换任务队列锁
    std::condition_variable cv_;
};

}
#endif //TINYNET_THREADPOOL_H
