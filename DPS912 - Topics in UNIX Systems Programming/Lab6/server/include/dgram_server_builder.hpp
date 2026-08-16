#ifndef L6_DGRAM_SERVER_BUILDER_HPP
#define L6_DGRAM_SERVER_BUILDER_HPP

#include "server_builder.hpp"
#include "core/address/inet_address.hpp"
#include "core/address/unix_address.hpp"
#include "core/socket/datagram_socket.hpp"

#include <string>

namespace L6 {
    template <class T>
    class DgramUdpServerBuilder : public ServerBuilder {
        static_assert((
                std::is_same_v<T, UnixAddress> 
                || std::is_same_v<T, InetAddress>
            ), 
            "Unsupported Type, only supports UnixAddress and InetAddress"
        );

    private:
        DatagramSocket server {};
        T client {};
        
    protected:
        void initServer(Address& address) override {
            this->server = std::move(DatagramSocket(address.family(), SOCK_DGRAM));
            if(this->server.bind(address) < 0) throw std::runtime_error("bind()");
        }

        void initConnection() override {
            // Expects a "ready" msg from client
            const int bufSize { 20 };
            char buf[bufSize];

            this->server.read(buf, bufSize - 1, this->client);
        }

        void write(const std::string& message) override { this->server.write(message, this->client); }
        ssize_t read(void* buf, const size_t& n) override { return this->server.read(buf, n, this->client); }
    public:
        DgramUdpServerBuilder() = default;
    };

    using DgramServerBuilder = DgramUdpServerBuilder<UnixAddress>;
    using UDPServerBuilder   = DgramUdpServerBuilder<InetAddress>;
};

#endif