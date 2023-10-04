//
// Created by Hain_official on 2023-10-02.
//

#ifndef TINYNET_BUFFER_H
#define TINYNET_BUFFER_H
#include <mutex>
#include <vector>
#include <string>
#include <string_view>
#include <optional>
#include <deque>
namespace tinynet {

static constexpr size_t INITIAL_BUFFER_CAPACITY = 1024;

class Buffer {
public:
    explicit Buffer(size_t initial_capacity = INITIAL_BUFFER_CAPACITY);
    ~Buffer() = default;

    Buffer(const Buffer &o) = default;
    Buffer &operator=(const Buffer &o) = default;

    void Append(const unsigned char *new_char_data, size_t data_size);

    void Append(const std::string &new_str_data);

    void Append(std::vector<unsigned char> &&other_buffer);

    void AppendHead(const unsigned char *new_char_data, size_t data_size);

    void AppendHead(const std::string &new_str_data);

    auto FindAndPopTill(const std::string &target) -> std::optional<std::string>;

    auto ToStringView() const noexcept -> std::string_view;

    auto Data() -> const unsigned char *;

    void Clear() noexcept;

    auto Size() const noexcept -> size_t;

    auto Capacity() const noexcept -> size_t;

private:
    std::vector<unsigned char> buf_;
};

}

#endif //TINYNET_BUFFER_H
