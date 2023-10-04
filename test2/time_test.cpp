//
// Created by Hain_official on 2023-09-29.
//
#include <bits/stdc++.h>
#include "Timer.h"
#include "ThreadPool.h"
using namespace tinynet;
using namespace std;

void print() { std::cout << std::endl; }

template<typename F, typename... Args>
void print(F &&f, Args&&... args) {
    std::cout << std::forward<F>(f) << " ";
    print(std::forward<Args>(args)...);
}

long long a[10];

void f(int x) {
    for (long long i = 1; i <= 10000000000; i++) {
        a[x]++;
    }
}

int main() {
    ThreadPool pool(5);
    for (int i = 0; i < pool.GetSize(); i++) {
        pool.Emplace(f, i);
    }
    auto begin = NowSinceEpoch();
    sleep(20);
    // f(1);
    auto end = NowSinceEpoch();
    ::println(a[0] + a[1] + a[2] + a[3] + a[4] + a[5] + a[6] + a[7] + a[8] + a[9]);
    ::println(end - begin);
}