//
// Created by Hain_official on 2023-09-14.
//
#include "ThreadPool.h"


namespace tinynet {

ThreadPool::ThreadPool(int size) {
    size = std::max(size, MIN_NUM_THREADS_IN_POOL);
    for (int i = 0; i < size; i++) {
        threads_.emplace_back([this]() {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mtx_);
                    cv_.wait(lock, [this]() { return stop_ || !tasks_.empty(); });
                    if (stop_ && tasks_.empty()) {
                        return;
                    }
                    task = tasks_.front();
                    tasks_.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    Exit();
    for (auto &worker : threads_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::Exit() {
    stop_ = true;
    cv_.notify_all();
}



}