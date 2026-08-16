#ifndef L6_DATAGRAM_SOCKET_HPP
#define L6_DATAGRAM_SOCKET_HPP

#include "core/socket/socket.hpp"
#include "core/address/address.hpp"
#include <string_view>

namespace L6 {
    class DatagramSocket : public Socket {
    public:
        DatagramSocket() = default;
        DatagramSocket(const int domain, const int type);
        ssize_t write(const std::string_view& message, Address& addr, int flags = 0);
        ssize_t read(void* buf, size_t size, Address& addr, int flags = 0);
    };
};

#endif