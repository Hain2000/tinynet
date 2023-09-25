//
// Created by Hain_official on 2023-09-14.
//

#ifndef TINYNET_UTILS_H
#define TINYNET_UTILS_H

#include <atomic>
#include "nocopyable.h"

namespace tinynet {

class spin_lock {
    std::atomic_flag flag_;
public:
    spin_lock() : flag_(ATOMIC_FLAG_INIT) {}
    void lock() {
        while (flag_.test_and_set(std::memory_order_acquire));
    }
    void unlock() {
        flag_.clear(std::memory_order_release);
    }
};

class spinlock_guard : nocopyable {
    spin_lock &lock_;
public:
    spinlock_guard(spin_lock &lock) : lock_(lock) {
        lock_.lock();
    }
    ~spinlock_guard() {
        lock_.unlock();
    }
};

}


#endif //TINYNET_UTILS_H
