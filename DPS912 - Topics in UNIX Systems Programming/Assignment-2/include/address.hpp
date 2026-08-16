#ifndef AS2_ADDRESS_HPP
#define AS2_ADDRESS_HPP

#include "logger.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string_view>
#include <stdexcept>
#include <unistd.h>

namespace AS2 {
    class Address {
    protected:
        socklen_t length{};
    public:
        virtual ~Address() = default;

        virtual void* data() = 0;
        virtual const void* data() const = 0;

        virtual socklen_t& size() = 0;
        virtual int family() const = 0;
    };

    class InetAddress : public Address {
    private:
        sockaddr_in address {};
    public:
        InetAddress(const std::string_view& ip, const uint16_t& port);
        InetAddress(sockaddr* addr, socklen_t& len);
        InetAddress();

        void* data() override;
        const void* data() const override;

        socklen_t& size() override;
        int family() const override;
    };
};

#endif