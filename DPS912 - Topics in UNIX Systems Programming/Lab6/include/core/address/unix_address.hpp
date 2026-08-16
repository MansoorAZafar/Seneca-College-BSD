#ifndef L6_UNIX_ADDRESS_HPP
#define L6_UNIX_ADDRESS_HPP

#include "core/address/address.hpp"
#include <string_view>
#include <stdexcept>
#include <sys/un.h>
#include <string>

namespace L6 {
    class UnixAddress : public Address {
    private:
        sockaddr_un address = {};
    public:
        UnixAddress();
        UnixAddress(const std::string_view& path);

        void* data() override;
        const void* data() const override;
        socklen_t& size() override;
        int family() const override;
    };
};

#endif