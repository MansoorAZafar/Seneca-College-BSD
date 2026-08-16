#ifndef L6_SOCK_SERVER_BUILDER_HPP
#define L6_SOCK_SERVER_BUILDER_HPP

#include "server_builder.hpp"
#include "core/address/inet_address.hpp"
#include "core/address/unix_address.hpp"
#include "core/socket/connection.hpp"
#include "core/socket/listener.hpp"

#include <string>

namespace L6 {
    template <class T>
    class SockServerBuilder : public ServerBuilder {
        static_assert((
                std::is_same_v<T, UnixAddress> 
                || std::is_same_v<T, InetAddress>
            ), 
            "Unsupported Type, only supports UnixAddress and InetAddress"
        );
        
    private:
        Listener server {};
        Connection conn {};
        T client;
        
    protected:
        void initServer(Address& address) override {
            this->server = std::move(Listener(address));
        }

        void initConnection() override {
            this->conn = this->server.accept(
                static_cast<sockaddr*>(this->client.data()),
                this->client.size()
            );
        }

        void write(const std::string& message) override { this->conn.write(message); }
        ssize_t read(void* buf, const size_t& n) override { return this->conn.read(buf, n); }
    public:
        SockServerBuilder() = default;
    };

    using StreamServerBuilder = SockServerBuilder<UnixAddress>;
    using TCPServerBuilder    = SockServerBuilder<InetAddress>;
};

#endif