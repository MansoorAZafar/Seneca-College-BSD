#ifndef L6_STREAM_SOCKET_HPP
#define L6_STREAM_SOCKET_HPP

#include <unistd.h>
#include <iostream>
#include <sys/types.h> // ssize_t
#include <string_view>
#include <sys/socket.h>
#include "core/socket/socket.hpp"
#include "core/address/address.hpp"

namespace L6 {
    class StreamSocket : public Socket {
    public:
        StreamSocket() = default;
        explicit StreamSocket(int existing_fd);
        StreamSocket(const int domain, const int type);

        int connect(Address& addr);
        ssize_t write(const std::string_view& message);
        ssize_t read(void*, const size_t&);
        ssize_t read_safe(void*, const size_t&);
    };
};

#endif