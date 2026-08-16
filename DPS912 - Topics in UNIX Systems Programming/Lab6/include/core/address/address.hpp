#ifndef L6_ADDRESS_HPP
#define L6_ADDRESS_HPP

#include <sys/socket.h>
#include <unistd.h>
#include <string>

namespace L6 {
    class Address {
    protected:
        socklen_t length {};
    public:
        virtual ~Address() = default;

        virtual void* data() = 0;
        virtual const void* data() const = 0;
        
        virtual socklen_t& size() = 0;
        virtual int family() const = 0;
    };
};

#endif