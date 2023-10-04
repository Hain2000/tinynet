//
// Created by Hain_official on 2023-09-14.
//

#ifndef TINYNET_UTILS_H
#define TINYNET_UTILS_H

#include <atomic>
#include <iostream>
#include <cassert>
namespace tinynet {


static void println() { std::cerr << '\n'; }

template<typename Head, typename... Tail>
static void println(Head H, Tail ...T) {
    std::cerr << H << " ";
    println(T...);
}

#define CHECK(ok)    \
    if (ok) {             \
        println("OK", __LINE__);    \
    } else {              \
        println("ERROR", __FILE__, __LINE__); \
    }



#define ThreadMillisecondSleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<uint64_t>(x)))

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

class spinlock_guard {
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
