#include "core/address/inet_address.hpp"
#include "utility/logger.hpp"

namespace L6 {
    InetAddress::InetAddress() {
        this->address.sin_family = AF_INET;
        this->length = sizeof(this->address);
    }
    
    InetAddress::InetAddress(const std::string_view& ip, const uint16_t& port) {
        l6_debug("Initialzing new Inet Address with ip: " + std::string(ip) + " and port: " + std::to_string(port));

        this->address = {};
        this->address.sin_family = AF_INET;
        this->address.sin_port = htons(port);

        this->length = sizeof(this->address);
        if(::inet_pton(AF_INET, ip.data(), &this->address.sin_addr) != 1) {
            throw std::runtime_error("inet_pton failed");
        }
    }

    void* InetAddress::data() {
        return &this->address;
    }

    const void* InetAddress::data() const {
        return &this->address;
    }

    socklen_t& InetAddress::size() {
        return this->length;
    }

    int InetAddress::family() const {
        return AF_INET;
    }
};