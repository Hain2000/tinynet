//
// Created by Hain_official on 2023-09-14.
//

#ifndef TINYNET_NOCOPYABLE_H
#define TINYNET_NOCOPYABLE_H

class nocopyable {
public:
    nocopyable(const nocopyable &) = delete;
    void operator=(const nocopyable &) = delete;
protected:
    nocopyable() = default;
    ~nocopyable() = default;
};

#endif //TINYNET_NOCOPYABLE_H
