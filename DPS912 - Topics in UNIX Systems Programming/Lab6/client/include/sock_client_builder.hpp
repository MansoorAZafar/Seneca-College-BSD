#ifndef L6_SOCK_CLIENT_BUILDER_HPP
#define L6_SOCK_CLIENT_BUILDER_HPP

#include "client_builder.hpp"
#include "core/address/address.hpp"
#include "core/address/inet_address.hpp"
#include "core/address/unix_address.hpp"
#include "core/socket/stream_socket.hpp"

namespace L6 {
    template <class T>
    class SockClientBuilder : public ClientBuilder {
        static_assert((
                std::is_same_v<T, UnixAddress> 
                || std::is_same_v<T, InetAddress>
            ), 
            "Unsupported Type, only supports UnixAddress and InetAddress"
        );
    
    protected:
        void initConnection() override {
            static_cast<StreamSocket*>(this->client)->connect(*this->server);
        }

        void write(const std::string& message) override { 
            static_cast<StreamSocket*>(this->client)->write(message);
        }

        ssize_t read(void* buf, const size_t& n) override { 
            return static_cast<StreamSocket*>(this->client)->read(buf, n);
        }

    public:
        SockClientBuilder() = default;
    };
    
    using TCPClientBuilder    = SockClientBuilder<InetAddress>;
    using StreamClientBuilder = SockClientBuilder<UnixAddress>;
};

#endif