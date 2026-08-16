#ifndef L6_CONNECTION_SOCKET_HPP
#define L6_CONNECTION_SOCKET_HPP

// For connection-orentiated servers (TCP & Sock Stream)
#include "core/socket/stream_socket.hpp"
#include <string_view>
#include <iostream>

namespace L6 {
    class Connection {
    private:
        StreamSocket socket;
    public:
        Connection() = default;
        
        explicit Connection(StreamSocket&&);
        StreamSocket& socket_ref();

        ssize_t read(void*, const size_t&);
        ssize_t write(const std::string_view& message);
    };
};

#endif