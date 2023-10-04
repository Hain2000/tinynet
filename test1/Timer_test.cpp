//
// Created by Hain_official on 2023-10-02.
//
#include "Timer.h"
#include <assert.h>
#include <thread>
#include <memory>
#include "NetAddress.h"
#include "Epoll.h"
#include "EventLoop.h"
using namespace tinynet;
uint64_t expire = 1000;

void f1_test() {
    println(__FUNCTION__ );
    SingleTimer single_timer(expire, nullptr);
    ThreadMillisecondSleep(expire * 0.9);
    CHECK(!single_timer.Expired());
    ThreadMillisecondSleep(expire * 0.2);
    CHECK(single_timer.Expired());
}

void f2_test() {
    println(__FUNCTION__ );
    int i = 0;
    SingleTimer single_timer2{expire, [&]() { i++; }};
    ThreadMillisecondSleep(expire * 1.1);
    if (single_timer2.Expired()) {
        single_timer2.Run();
    }
    CHECK(single_timer2.Expired());
    CHECK(i == 1);
}

void f3_test() {
    println(__FUNCTION__ );
    Timer t;
    CHECK(t.NextExpireTime() == 0);
    auto now = NowSinceEpoch();
    t.AddSingleTimer(200, nullptr);
    t.AddSingleTimer(100, nullptr);
    t.AddSingleTimer(500, nullptr);
    auto next_expire = t.NextExpireTime();
    CHECK((next_expire < (now + 110) && next_expire > (now + 90)));
    CHECK(t.TimerCount() == 3);
}

void f4_test() {
    println(__FUNCTION__ );
    Timer t;
    CHECK(t.NextExpireTime() == 0);
    auto now = NowSinceEpoch();
    auto raw_timer = t.AddSingleTimer(200, nullptr);
    auto next_expire = t.NextExpireTime();
    CHECK((next_expire < (now + 210) && next_expire > (now + 190)));
    ThreadMillisecondSleep(200);
    t.RefreshSingleTimer(raw_timer, 200);
    next_expire = t.NextExpireTime();
    CHECK((next_expire < (now + 410) && next_expire > (now + 390)));
}

void f5_test() {
    println(__FUNCTION__ );
    Timer t;
    t.AddSingleTimer(200, nullptr);
    auto expire_1 = t.NextExpireTime();
    auto raw_ptr = t.AddSingleTimer(100, nullptr);
    t.AddSingleTimer(500, nullptr);
    auto expire_2 = t.NextExpireTime();
    CHECK(expire_2 < expire_1);
    CHECK(t.RemoveSingleTimer(raw_ptr) == true);
    CHECK(t.TimerCount() == 2);
    CHECK(expire_1 == t.NextExpireTime());
}

void f6_test() {
    println(__FUNCTION__ );
    Timer t;
    t.AddSingleTimer(400, nullptr);
    t.AddSingleTimer(100, nullptr);
    t.AddSingleTimer(500, nullptr);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    auto expired = t.PruneExpiredTimer();
    CHECK(expired.size() == 1);
    CHECK(t.TimerCount() == 2);
    auto now = NowSinceEpoch();
    auto next_expire = t.NextExpireTime();
    CHECK((next_expire > (now + 150) && next_expire < (now + 250)));
}

void f7_test() {
    Epoll poller;
    Timer t;
    int timeout = 100;
    poller.AddConnection(t.GetTimerConnection());
    auto triggered = poller.Poll(timeout);
    CHECK(triggered.empty());
    t.AddSingleTimer(100, nullptr);
    t.AddSingleTimer(200, nullptr);
    t.AddSingleTimer(300, nullptr);
    std::this_thread::sleep_for(std::chrono::milliseconds(110));
    triggered = poller.Poll(timeout);
    CHECK(triggered.size() == 1);
    auto expired = t.PruneExpiredTimer();
    CHECK(expired.size() == 1);
    CHECK(t.TimerCount() == 2);
    auto now = NowSinceEpoch();
    auto next_expire = t.NextExpireTime();
    CHECK((next_expire > now + 75 && next_expire < now + 125));
}



int main() {
    f7_test();

}