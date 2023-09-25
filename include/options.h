//
// Created by Hain_official on 2023-09-14.
//

#ifndef TINYNET_OPTIONS_H
#define TINYNET_OPTIONS_H
#include <string>
#include <unistd.h>

namespace tinynet {
    namespace options {

        constexpr static unsigned kThreadPoolNum = 4; // 线程池中线程的数量


        constexpr static unsigned kBackLog = 8192; // 监听队列的长度

    }
}


#endif //TINYNET_OPTIONS_H
