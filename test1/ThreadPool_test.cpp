//
// Created by Hain_official on 2023-09-25.
//

#include "ThreadPool.h"
#include <iostream>
using namespace std;
using namespace tinynet;


int main() {
    ThreadPool pool(4);
    cout << (pool.GetSize() == 4) << endl;
    std::atomic<int> x{0};
    for (int i = 0; i < 24; i++) {
        pool.Emplace([&]() {
           x++;
        });
    }
    cout << (x) << endl;
}