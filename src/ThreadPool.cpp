//
// Created by Hain_official on 2023-09-14.
//
#include "ThreadPool.h"
#include "options.h"
using namespace tinynet;

thread_pool::thread_pool()
    : usable_q_(0)
    , stop_(false) {

    for (size_t i = 0; i < options::kThreadPoolNum; i++) {
        workers_.emplace_back([this] {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(thread_mtx_);
                    this->cv_.wait(lock, [this] {
                        return stop_ || !tasks_[usable_q_].empty() || tasks_[!usable_q_].empty();
                    });

                    if (stop_ && tasks_[usable_q_].empty() && tasks_[!usable_q_].empty()) {
                        return;
                    }

                    // 另一个任务队列为空的话，就把当前
                    int task_q = !usable_q_;
                    if (tasks_[task_q].empty()) {
                        q_mtx_.lock();
                        usable_q_ = task_q;
                        q_mtx_.unlock();
                    }
                    task_q = !usable_q_;

                    try {
                        task = std::move(tasks_[task_q].front());
                        tasks_[task_q].pop();
                    } catch (std::exception &e) {
                        // log
                    }

                }

                try {
                    task();
                } catch (std::exception &e) {
                    // log
                }

            }
        });
    }

}

void thread_pool::Emplace(std::function<void()> &&f) {
    if (stop_) {
        // log
        return;
    }
    std::unique_lock<std::mutex> lock(thread_mtx_);
    tasks_[usable_q_].emplace(std::move(f));
    lock.unlock();
    cv_.notify_one();
}

thread_pool::~thread_pool() {
    std::unique_lock<std::mutex> lock(thread_mtx_);
    stop_ = true;
    lock.unlock();
    cv_.notify_all();
    for (auto &wk : workers_) {
        wk.join();
    }
}