#include "socket.hpp"
namespace AS2 {
    Socket::Socket(const int fd)
        : m_fd(fd) {
        mz::debug("[Socket] Initializing Socket with existing_fd: " + std::to_string(fd));
    }

    Socket::Socket(const int domain, const int type)
        : m_fd(::socket(domain, type, 0)) {
        mz::debug("[Socket] Initializing new Socket with fd: " + std::to_string(this->m_fd));
        
        if(this->m_fd == -1) {
            throw std::runtime_error("socket()");
        }

        mz::debug("[Socket] successfully initialized");
    }
    
    Socket::Socket(Socket&& other) {
        mz::debug("[Socket] Moving Socket constructor Socket(Socket&&)");
        mz::debug("[Socket] other.fd: " + std::to_string(other.m_fd) + " this->fd: " + std::to_string(this->m_fd));

        *this = std::move(other);
        mz::debug("[Socket] Socket Move constructor DONE Socket(Socket&&)");
    }

    Socket& Socket::operator=(Socket&& other) {
        mz::debug("[Socket] Moving Socket operator=");
        mz::debug("[Socket] other.fd: " + std::to_string(other.m_fd) + " this->fd: " + std::to_string(this->m_fd));

        if(this != &other) {
            if(this->m_fd != -1) ::close(this->m_fd);
            
            this->m_fd = other.m_fd;
            other.m_fd = -1;
        }

        mz::debug("[Socket] Socket Moved operator= DONE");
        return *this;
    }

    int Socket::bind(Address& address) {
        const sockaddr* addr { static_cast<const sockaddr*>(address.data()) };
        const std::string log_msg { "[Socket] Binding Socket" };
        mz::info(log_msg);

        return ::bind(
            this->m_fd,
            addr,
            address.size()
        );
    }

    int Socket::fd() const {
        return this->m_fd;
    }

    Socket::~Socket() {
        const std::string log_msg { "[Socket] Freeing Socket: " + std::to_string(this->m_fd) };
        mz::debug(log_msg);

        if(this->m_fd != -1) ::close(this->m_fd);
    }
    
    
    StreamSocket::StreamSocket(const int fd)
        : Socket(fd) {
        mz::debug("[StreamSocket] init with existing fd: " + std::to_string(fd));
    }
    
    StreamSocket::StreamSocket(const int domain, const int type)
        : Socket(domain, type) {
        mz::debug("[StreamSocket] new init with fd: " + std::to_string(this->m_fd));
    }
    
    int StreamSocket::connect(Address &addr) {
        mz::debug("[StreamSocket] connected to address");
        return ::connect(
            this->m_fd,
            static_cast<const sockaddr*>(addr.data()),
            addr.size()
        );
    }
    
    ssize_t StreamSocket::write(const std::string_view& buffer) {
        mz::debug("[StreamSocket] Sending message: " + std::string(buffer.data()));
        return ::write(
            this->m_fd,
            buffer.data(),
            buffer.size()
        );
    }
    
    ssize_t StreamSocket::read(void* buffer, const size_t& n) {
        mz::debug("[StreamSocket] reading incoming message");
        return ::read(
            this->m_fd,
            buffer,
            n
        );
    }

    bool StreamSocket::write_full_message(const void* buf, size_t count) {
        const char* p { static_cast<const char*>(buf) };
        while(count > 0) {
            ssize_t bytes { ::write(this->m_fd, p, count) };
            if(bytes <= 0) {
                mz::warn("[StreamSocket] Write_full_message Error or Closed conn");
                return false;
            }

            p += bytes;
            count -= bytes;
        }

        return true;
    }

    bool StreamSocket::read_full_message(void* buf, size_t count) {
        char* p { static_cast<char*>(buf) };
        while(count > 0) {
            ssize_t bytes { ::read(this->m_fd, p, count) };
            if(bytes <= 0) {
                mz::warn("[StreamSocket] Read_full_message Error or Closed conn");
                return false;
            }

            p += bytes;
            count -= bytes;
        }

        return true;
    }

    bool StreamSocket::write_all(const std::string_view& buffer) {
        const uint32_t length { ::htonl(static_cast<uint32_t>(buffer.size())) };

        if(!this->write_full_message(&length, sizeof(length))) {
            mz::warn("[StreamSocket]: Failed to write length prefix");
            return false;
        };        

        return this->write_full_message(buffer.data(), buffer.size());
    }

    std::string StreamSocket::read_all() {
        uint32_t length { 0 };
        if(!this->read_full_message(&length, sizeof(length))) {
            mz::warn("[StreamSocket]: Failed to read length prefix");
            return "";
        }

        uint32_t message_length = ::ntohl(length);
        std::vector<char> buffer(message_length);

        if(!this->read_full_message(buffer.data(), message_length)) {
            mz::warn("[StreamSocket]: Failed to read full message");
            return "";
        }

        return std::string(buffer.begin(), buffer.end());
    }
};