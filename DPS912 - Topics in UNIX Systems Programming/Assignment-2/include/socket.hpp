#ifndef AS1_SOCKET_HPP
#define AS1_SOCKET_HPP

#include <sys/socket.h>
#include <string_view>
#include "address.hpp"
#include "logger.hpp"
#include <vector>
#include <string>
#include <span>

namespace AS2 {
    class Socket {
    protected:
        int m_fd { -1 };
        explicit Socket(const int fd);
    public:
        Socket() = default;
        Socket(const int domain, const int type);        
        
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;
        
        Socket(Socket&&);
        Socket& operator=(Socket&&);

        int bind(Address& addr);
        int fd() const;
        virtual ~Socket();
    };

    class StreamSocket : public Socket {
    private:
        bool write_full_message(const void* buf, size_t count);
        bool read_full_message(void* buf, size_t count);
    public:
        StreamSocket() = default;
        StreamSocket(const int fd);
        StreamSocket(const int domain, const int type);    

        int connect(Address& addr); 
        ssize_t write(const std::string_view& buffer);
        ssize_t read(void* buffer, const size_t& n);

        bool write_all(const std::string_view& buffer);
        std::string read_all();
    };

    template <class T>
    class Connection {
    private:
        static_assert(
            std::is_same_v<T, InetAddress>,
            "Connection must be type InetAddress"
        );

        StreamSocket socket {};
        T client {};
    public:
        explicit Connection(StreamSocket&& other, const T& addr)
            : socket(std::move(other)) {
            this->client = addr;
            mz::info("[Connection] creating a new connection");
        }

        StreamSocket& socket_ref() { return this->socket; }
        int fd() const { return this->socket.fd(); };

        ssize_t read(void* buffer, const size_t& n) { return this->socket.read(buffer, n); }
        ssize_t write(const std::string_view& buffer) { return this->socket.write(buffer); }
        
        bool write_all(const std::string_view& buffer) { return this->socket.write_all(buffer); }
        std::string read_all() { return this->socket.read_all(); }
    };

    template <class T>
    class Listener {
    private:
        static_assert(
            std::is_same_v<T, InetAddress>,
            "Listener must be type InetAddress"
        );

        StreamSocket socket {};
    public:
        Listener() = default;
        Listener(Address& addr, const int backlog = 5)
            : socket(addr.family(), SOCK_STREAM) {
            mz::debug("[Listener] constructor");

            if(this->socket.bind(addr) < 0) {
                mz::warn("[Listener] bind() error");
                throw std::runtime_error("bind()");
            }
            
            mz::info("[Listener] listening");
            if(::listen(this->socket.fd(), backlog) == -1) {
                mz::warn("[Listener] listen() error");
                throw std::runtime_error("listen()");
            }
        }

        int fd() const { return this->socket.fd(); }

        Connection<T> accept() {
            mz::info("[Listener] Accepting Client");
            
            sockaddr_storage storage{};
            socklen_t len = sizeof(storage);

            const int client_fd { ::accept(this->socket.fd(), reinterpret_cast<sockaddr*>(&storage), &len) };
            T address {reinterpret_cast<sockaddr*>(&storage), len};

            if(client_fd == -1) {
                mz::warn("[Listener] accept() error");
                throw std::runtime_error("accept()");
            }

            mz::info("[Listener] Client Accepted, client fd: " + std::to_string(client_fd));
            return Connection<T>(StreamSocket(client_fd), address);
        }
    };
};
#endif