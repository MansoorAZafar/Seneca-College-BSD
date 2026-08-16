#ifndef L6_LISTENER_SOCKET_HPP
#define L6_LISTENER_SOCKET_HPP

#include "core/socket/stream_socket.hpp"
#include "core/socket/connection.hpp"
#include "core/address/address.hpp"

namespace L6 {

    // For connection-orentiated servers (TCP & Sock Stream)
    class Listener {
    private:
        StreamSocket socket;
        std::string path; 
    public:
        Listener() = default;
        Listener(Address&, const int = 5);
        Connection accept(sockaddr* addr, socklen_t& len);
    };
};

#endif