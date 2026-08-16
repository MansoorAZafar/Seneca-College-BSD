#ifndef LAB_6_SOCKET_HPP
#define LAB_6_SOCKET_HPP

#include "core/address/address.hpp"

namespace L6 {

    class Socket {
    protected:
        int fd { -1 };
        explicit Socket(const int existing_fd);
    public:
        Socket() = default;
        Socket(const int domain, const int type);
    
        /*
        * We are removing the copy operations since we want to follow RAII.
        * Any Socket object should OWN that fd, so there cannot be issues with closing the fd.
        * If we had Socket a; Socket b = a; if A closes it's fd, then B will be broken, to avoid that
        * we want all Sockets that have a fd to be the ONLY owner. So we support move but NOT copy
        */
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        Socket(Socket&&);
        Socket& operator=(Socket&&);

        int bind(Address& address);
        int file_descriptor() const;

        virtual ~Socket();
    };
};

#endif


