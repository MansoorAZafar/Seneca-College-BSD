#include "core/socket/stream_socket.hpp"
#include "utility/logger.hpp"

namespace L6 {

    StreamSocket::StreamSocket(int existing_fd)
        : Socket(existing_fd) {
            l6_debug("[StreamSocket] init with existing fd: " + std::to_string(existing_fd));
        }
    
    StreamSocket::StreamSocket(const int domain, const int type)
        : Socket(domain, type) {
            l6_debug("[StreamSocket] new init with fd: " + std::to_string(this->fd));
        }

    int StreamSocket::connect(Address& addr) {
        l6_debug("[StreamSocket] connected to address");
        return ::connect(
            this->fd,
            static_cast<const sockaddr*>(addr.data()),
            addr.size()
        );
    }  

    ssize_t StreamSocket::write(const std::string_view& message) {
        l6_debug("[StreamSocket] Sending message: " + std::string(message));
        return ::send(
            this->fd,
            message.data(),
            message.size(),
            0
        );
    }

    ssize_t StreamSocket::read(void* buf, const size_t& n) {
        l6_debug("[StreamSocket] reading incoming message");
        return ::read(
            this->fd,
            buf,
            n
        );
    }

    ssize_t StreamSocket::read_safe(void* buf, const size_t& n) {
        return this->read(buf, n - 1);
    }
    
};