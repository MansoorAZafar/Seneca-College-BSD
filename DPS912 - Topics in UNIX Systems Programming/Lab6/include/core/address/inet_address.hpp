#ifndef L6_INET_ADDRESS_HPP
#define L6_INET_ADDRESS_HPP

#include "core/address/address.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string_view>
#include <stdexcept>

namespace L6 {
    class InetAddress : public Address {
    private:
        sockaddr_in address = {};
    public:
        InetAddress();
        InetAddress(const std::string_view& ip, const uint16_t& port);

        void* data() override;
        const void* data() const override;
        socklen_t& size() override;
        int family() const override;
    };
};

#endif