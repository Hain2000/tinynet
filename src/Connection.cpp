//
// Created by Hain_official on 2023-09-29.
//

#include "Connection.h"
#include "Logger.h"
namespace tinynet {

constexpr static int TEMP_BUF_SIZE = 2048;

Connection::Connection(std::unique_ptr<Socket> socket)
    : socket_(std::move(socket))
    , read_buf_(std::make_unique<Buffer>())
    , write_buf_(std::make_unique<Buffer>()) {}

auto Connection::GetFd() const noexcept -> int {
    return socket_->GetFd();
}

auto Connection::GetSocket() noexcept -> Socket * {
    return socket_.get();
}

void Connection::SetEvents(uint32_t events) {
    events_ = events;
}

auto Connection::GetEvents() const noexcept -> uint32_t {
    return events_;
}

void Connection::SetRevents(uint32_t revents) {
    revents_ = revents;
}

auto Connection::GetRevents() const noexcept -> uint32_t {
    return revents_;
}

void Connection::SetCallBack(const std::function<void(Connection *)> &callback) {
    callback_ = [callback, this] { callback(this); };
}

auto Connection::GetCallBack() noexcept -> std::function<void()> {
    return callback_;
}


void Connection::SetLooper(tinynet::EventLoop *loop) noexcept {
    loop_ = loop;
}

auto Connection::GetLooper() noexcept -> EventLoop * {
    return loop_;
}

auto Connection::FindAndPopTill(const std::string &target) -> std::optional<std::string> {
    return read_buf_->FindAndPopTill(target);
}

auto Connection::GetReadBufferSize() const noexcept -> size_t {
    return read_buf_->Size();
}

auto Connection::GetWriteBufferSize() const noexcept -> size_t {
    return write_buf_->Size();
}

void Connection::WriteToReadBuffer(const unsigned char *buf, size_t size) {
    read_buf_->Append(buf, size);
}

void Connection::WriteToWriteBuffer(const unsigned char *buf, size_t size) {
    write_buf_->Append(buf, size);
}

void Connection::WriteToReadBuffer(const std::string &str) {
    read_buf_->Append(str);
}

void Connection::WriteToWriteBuffer(const std::string &str) {
    write_buf_->Append(str);
}

void Connection::WriteToWriteBuffer(std::vector<unsigned char> &&other_buf) {
    write_buf_->Append(std::move(other_buf));
}

auto Connection::Read() const noexcept -> const unsigned char * {
    return read_buf_->Data();
}

auto Connection::ReadAsString() const noexcept -> std::string {
    auto str_view = read_buf_->ToStringView();
    return {str_view.begin(), str_view.end()};
}

auto Connection::Recv() -> std::pair<ssize_t, bool> {
    int from_fd = GetFd();
    ssize_t read_n = 0;
    unsigned char buf[TEMP_BUF_SIZE + 1];
    memset(buf, 0, sizeof(buf));
    while (true) {
        ssize_t cur_read = recv(from_fd, buf, TEMP_BUF_SIZE, 0);
        if (cur_read > 0) {
            read_n += cur_read;
            WriteToReadBuffer(buf, cur_read);
            memset(buf, 0, sizeof(buf));
        } else if (cur_read == 0) { // 客户端存在
            return {read_n, true};
        } else if (cur_read == -1 && errno == EINTR) { // 正常中断
            continue;
        } else if (cur_read == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {

            break;
        } else {
            LOG_ERROR("Connection: revc() err");
            return {read_n, true};
        }
    }
    return {read_n, false};
}

void Connection::Send() {
    int to_fd = GetFd();
    ssize_t write_n = 0;
    const ssize_t to_write_size = GetWriteBufferSize();
    const unsigned char *buf = write_buf_->Data();
    while (write_n < to_write_size) {
        ssize_t cur_write = send(to_fd, buf + write_n, to_write_size - write_n, 0);
        if (cur_write <= 0) {
            if (errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK) {
                LOG_ERROR("Connection: Send() err");
                ClearWriteBuffer();
                return;
            }
            cur_write = 0;
        }
        write_n += cur_write;
    }
    ClearWriteBuffer();
}

void Connection::ClearReadBuffer() noexcept {
    read_buf_->Clear();
}

void Connection::ClearWriteBuffer() noexcept {
    write_buf_->Clear();
}

}