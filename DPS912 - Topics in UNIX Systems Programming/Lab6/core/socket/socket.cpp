#include "core/socket/socket.hpp"
#include "utility/logger.hpp"
#include <sys/socket.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>

namespace L6 {
    Socket::Socket(const int existing_fd)
        : fd(existing_fd) {
        l6_debug("[Socket] Initializing Socket with existing_fd: " + std::to_string(existing_fd));
    }
    
    Socket::Socket(const int domain, const int type)
        : fd(::socket(domain, type, 0)) {
        l6_debug("[Socket] Initializing new Socket with fd: " + std::to_string(this->fd));
     
        if(this->fd == -1) {
            throw std::runtime_error("socket()");
        }

        l6_debug("[Socket] successfully initialized");
    }

    Socket::Socket(Socket&& other) {
        l6_debug("[Socket] Moving Socket constructor Socket(Socket&&)");
        l6_debug("[Socket] other.fd: " + std::to_string(other.fd) + " this->fd: " + std::to_string(this->fd));

        *this = std::move(other);
        l6_debug("[Socket] Socket Move constructor DONE Socket(Socket&&)");
    }

    Socket& Socket::operator=(Socket&& other) {
        l6_debug("[Socket] Moving Socket operator=");
        l6_debug("[Socket] other.fd: " + std::to_string(other.fd) + " this->fd: " + std::to_string(this->fd));

        if(this != &other) {
            if(this->fd != -1) ::close(this->fd);
            
            this->fd = other.fd;
            other.fd = -1;
        }

        l6_debug("[Socket] Socket Moved operator= DONE");
        return *this;
    }

    int Socket::bind(Address& address) {
        const sockaddr* addr { static_cast<const sockaddr*>(address.data()) };
        const std::string log_msg { "[Socket] Binding Socket" };
        l6_info(log_msg);

        return ::bind(
            this->fd,
            addr,
            address.size()
        );
    }

    int Socket::file_descriptor() const {
        return this->fd;
    }

    Socket::~Socket() {
        const std::string log_msg { "[Socket] Freeing Socket: " + std::to_string(this->fd) };
        l6_debug(log_msg);

        if(this->fd != -1) ::close(this->fd);
    }
};