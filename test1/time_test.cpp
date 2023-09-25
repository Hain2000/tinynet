//
// Created by Hain_official on 2023-09-15.
//
#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <unistd.h>
using namespace std;

void test1() {
    time_t raw_time;
    ::time(&raw_time);
    cout << raw_time << endl; // 返回一个秒
    struct tm *time_info = localtime(&raw_time); // 具体时间
    cout << time_info->tm_year + 1900 << "年" << endl;
    cout << time_info->tm_mon + 1 << "月" << endl;
    cout << time_info->tm_mday << "日" << endl;
    cout << time_info->tm_hour << "时" << endl;
    cout << time_info->tm_min << "分" << endl;
    cout << time_info->tm_sec << "秒" << endl;
    cout << "星期" << time_info->tm_wday << endl;
    cout << asctime(time_info) << endl;
    cout << ctime(&raw_time) << endl;
}

void test2() {
    struct timeval a, b;
    gettimeofday(&a, nullptr); // 记录时间a
    sleep(2);
    gettimeofday(&b, nullptr); // 记录时间b
    cout << "针对秒级别：" << endl;
    cout << a.tv_sec << endl;
    cout << b.tv_sec << endl;
    cout << b.tv_sec - a.tv_sec << endl;

    cout << "针对微秒级别：" << endl;
    cout << a.tv_usec << endl;
    cout << a.tv_usec << endl;
    cout << b.tv_usec - a.tv_usec << endl;
}

void test3() {

}


int main() {
    test2();
}