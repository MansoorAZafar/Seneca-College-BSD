#ifndef L6_DGRAM_CLIENT_BUILDER_HPP
#define L6_DGRAM_CLIENT_BUILDER_HPP

#include "client_builder.hpp"
#include "core/address/address.hpp"
#include "core/address/inet_address.hpp"
#include "core/address/unix_address.hpp"
#include "core/socket/datagram_socket.hpp"
#include <string>
#include <string_view>

namespace L6 {

    template <class T>
    class DgramUdpClientBuilder : public ClientBuilder {
        static_assert((
                std::is_same_v<T, UnixAddress> 
                || std::is_same_v<T, InetAddress>
            ), 
            "Unsupported Type, only supports UnixAddress and InetAddress"
        );
    
    protected:
        T server_res {};

        void initConnection() override {
            // Expects a "ready" msg from client
            this->write("ready");
        }

        void write(const std::string& message) override { 
            static_cast<DatagramSocket*>(this->client)->write(message, *this->server);
            // this->client->write(message, *this->server); 
        }

        ssize_t read(void* buf, const size_t& n) override { 
            return static_cast<DatagramSocket*>(this->client)->read(buf, n, this->server_res);
            // return this->client->read(buf, n, this->server_res); 
        }
    public:
        DgramUdpClientBuilder() = default;
    };

    using UDPClientBuilder   = DgramUdpClientBuilder<InetAddress>;
    using DgramClientBuilder = DgramUdpClientBuilder<UnixAddress>; 
};
#endif