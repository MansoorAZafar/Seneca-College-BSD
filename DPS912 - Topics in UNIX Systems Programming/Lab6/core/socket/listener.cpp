#include "core/socket/listener.hpp"
#include "utility/logger.hpp"
#include <stdexcept>
#include <iostream>

namespace L6 {
    Listener::Listener(Address& addr, const int backlog) : socket(addr.family(), SOCK_STREAM) {
        l6_debug("[Listener] constructor");

        if(this->socket.bind(addr) < 0) {
            std::cout << "WEIRD ISSUE\n";
        }
        
        l6_info("[Listener] listening");
        if(::listen(this->socket.file_descriptor(), backlog) == -1) {
            l6_warn("[Listener] listen() error");
            throw std::runtime_error("listen()");
        }
    }

    Connection Listener::accept(sockaddr* addr, socklen_t& len) {
        l6_info("[Listener] Accepting Client");

        const int client_fd { ::accept(this->socket.file_descriptor(), addr, &len) };
        if(client_fd == -1) {
            l6_warn("[Listener] accept() error");
            throw std::runtime_error("accept()");
        }

        l6_info("[Listener] Client Accepted, client fd: " + std::to_string(client_fd));
        return Connection(StreamSocket(client_fd));
    }
};