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
#include <future>
#include <utility>
#include <type_traits>
namespace tinynet {

static constexpr int MIN_NUM_THREADS_IN_POOL = 2;


class ThreadPool {
public:

    explicit ThreadPool(int size = std::thread::hardware_concurrency() - 1);

    ~ThreadPool();

    template <typename F, typename... Args>
    decltype(auto) Emplace(F &&new_task, Args &&...args);

    void Exit();

    auto GetSize() -> size_t { return threads_.size(); };

private:
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::atomic<bool> stop_{false};
};

template <typename F, typename... Args>
auto ThreadPool::Emplace(F &&new_task, Args &&...args) -> decltype(auto) {
    using return_type = std::invoke_result_t<F, Args...>;
    if (stop_) {
        throw std::runtime_error("ThreadPool: Emplace() called while already stop");
    }
    auto packaged_new_task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(new_task), std::forward<Args>(args)...));
    auto res = packaged_new_task->get_future();
    {
        std::unique_lock<std::mutex> lock(mtx_);
        tasks_.emplace([packaged_new_task]() { (*packaged_new_task)(); });
    }
    cv_.notify_one();
    return res;
}


}
#endif //TINYNET_THREADPOOL_H

