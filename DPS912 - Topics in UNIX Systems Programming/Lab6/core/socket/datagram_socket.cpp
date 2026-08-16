#include "core/socket/datagram_socket.hpp"
namespace L6 {
    ssize_t DatagramSocket::write(const std::string_view& message, Address& addr, int flags) {
    return ::sendto(
            this->fd,
            message.data(),
            message.size(),
            flags,
            static_cast<const sockaddr*>(addr.data()),
            addr.size()
        );
    }

    ssize_t DatagramSocket::read(void* buf, size_t size, Address& addr, int flags) {
        return ::recvfrom(
            this->fd,
            buf,
            size,
            flags,
            static_cast<sockaddr*>(addr.data()),
            &addr.size()
        );
    }

    DatagramSocket::DatagramSocket(const int domain, const int type) 
        : Socket(domain, type) {}
};