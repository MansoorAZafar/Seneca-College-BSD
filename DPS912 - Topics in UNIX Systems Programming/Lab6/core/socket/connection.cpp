#include "core/socket/connection.hpp"
#include "utility/logger.hpp"

namespace L6 {
    Connection::Connection(StreamSocket&& sock)
        : socket(std::move(sock)) {
            l6_info("[Connection] creating a new connection");
        }

    StreamSocket& Connection::socket_ref() { return this->socket; }

    ssize_t Connection::read(void* buf, const size_t& n) {
        return this->socket.read(buf, n);
    }

    ssize_t Connection::write(const std::string_view& message) {
        return this->socket.write(message);
    }
};