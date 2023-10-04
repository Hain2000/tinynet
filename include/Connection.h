//
// Created by Hain_official on 2023-09-29.
//

#ifndef TINYNET_CONNECTION_H
#define TINYNET_CONNECTION_H
#include <memory>
#include <Socket.h>
#include <functional>
#include "Buffer.h"
namespace tinynet {
// 相当于muduo Channel + Connection

class EventLoop;

class Connection {
public:

    Connection(std::unique_ptr<Socket> socket);
    ~Connection() = default;

    auto GetFd() const noexcept ->  int;
    auto GetSocket() noexcept -> Socket *;

    void SetEvents(uint32_t events);
    auto GetEvents() const noexcept -> uint32_t;
    void SetRevents(uint32_t revents);
    auto GetRevents() const noexcept -> uint32_t;

    void SetCallBack(const std::function<void(Connection *)> &callback);
    auto GetCallBack() noexcept -> std::function<void()>;

    void SetLooper(EventLoop *loop) noexcept;
    auto GetLooper() noexcept -> EventLoop *;

    auto FindAndPopTill(const std::string &target) -> std::optional<std::string>;
    auto GetReadBufferSize() const noexcept -> size_t;
    auto GetWriteBufferSize() const noexcept -> size_t;
    void WriteToReadBuffer(const unsigned char *buf, size_t size);
    void WriteToWriteBuffer(const unsigned char *buf, size_t size);
    void WriteToReadBuffer(const std::string &str);
    void WriteToWriteBuffer(const std::string &str);
    void WriteToWriteBuffer(std::vector<unsigned char> &&other_buf);

    auto Read() const noexcept -> const unsigned char *;
    auto ReadAsString() const noexcept -> std::string;

    auto Recv() -> std::pair<ssize_t, bool>;
    void Send();
    void ClearReadBuffer() noexcept;
    void ClearWriteBuffer() noexcept;


private:
    EventLoop *loop_{nullptr};
    std::unique_ptr<Socket> socket_;
    uint32_t events_{0};
    uint32_t revents_{0};
    std::function<void()> callback_{nullptr};
    std::unique_ptr<Buffer> read_buf_;
    std::unique_ptr<Buffer> write_buf_;
};

}


#endif //TINYNET_CONNECTION_H
