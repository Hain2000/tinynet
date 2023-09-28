//
// Created by Hain_official on 2023-09-27.
//
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>

void Nonblock() {
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flags);
    char buf[1024];
    ssize_t n;
    while (true) {
        n = read(0, buf, 1024);
        if (n >= 0) break;
        if (errno != EAGAIN) {
            exit(1);
        }
        write(1, "again?\n", 7);
        sleep(3);
    }
    write(1, buf, n);
}


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage:cmd fd\n");
        exit(1);
    }
    int flags;
    if ((flags = fcntl(atoi(argv[1]), F_GETFL)) < 0) {
        perror("fcntl get flags");
        exit(1);
    }

    printf("flags=%#x\n", flags);
    printf("O_RDONLY=%#x\n", O_RDONLY);
    printf("O_WRONLY=%#x\n", O_WRONLY);
    printf("O_RDWR=%#x\n", O_RDWR);
    printf("O_APPEND=%#x\n", O_APPEND);
    printf("O_NONBLOCK=%#x\n", O_NONBLOCK);
    printf("O_ACCMODE=%#x\n", O_ACCMODE);
}