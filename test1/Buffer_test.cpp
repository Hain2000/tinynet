//
// Created by Hain_official on 2023-10-03.
//
#include "utils.h"
#include "Buffer.h"
#include <cstring>
#include <thread>
#include <unistd.h>
using namespace tinynet;



int main() {
    Buffer buffer;
    assert(buffer.Size() == 0);
    assert(buffer.Capacity() == INITIAL_BUFFER_CAPACITY);

    auto f1 = [&] {
        const char msg1[1024] = "Greeting from beginning!";
        const char msg2[2014] = "Farewell from end~";
        buffer.AppendHead(msg1);
        buffer.Append(msg2);
        snprintf((char *) msg1 + strlen(msg1), strlen(msg2) + 1, "%s", msg2);
        CHECK(std::strncmp((char *) buffer.Data(), msg1, std::strlen(msg1)) == 0);
        buffer.Clear();
        CHECK(buffer.Size() == 0);
    };


    auto f2 = [&] {
        const std::string msg1 = "Greeting from beginning!";
        const std::string msg2 = "Farewell from end~";
        buffer.AppendHead(msg1);
        buffer.Append(msg2);
        const std::string together = msg1 + msg2;
        CHECK(buffer.ToStringView() == together);
        buffer.Clear();
        CHECK(buffer.Size() == 0);
    };


    auto f3 = [&] {
        const std::string msg =
                "GET / HTTP/1.1\r\n"
                "Connection: Keep-Alive\r\n"
                "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                "Accept-Language: en-us\r\n"
                "\r\n";
        const std::string next_msg = "Something belongs to next message";
        buffer.Append(msg);
        buffer.Append(next_msg);
        auto op_str = buffer.FindAndPopTill("\r\n\r\n");
        CHECK((op_str.has_value() && op_str.value() == msg));
        CHECK(buffer.ToStringView() == next_msg);
    };


}