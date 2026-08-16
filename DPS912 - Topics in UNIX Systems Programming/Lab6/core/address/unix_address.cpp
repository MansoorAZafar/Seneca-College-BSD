#include "core/address/unix_address.hpp"
#include "utility/logger.hpp"

namespace L6 {
    UnixAddress::UnixAddress() {
        this->address = {};
        this->address.sun_family = AF_UNIX;
        this->length = sizeof(this->address);
    }
    
    UnixAddress::UnixAddress(const std::string_view& path) {
        l6_debug("Initialzing new Unix Address with path: " + std::string(path));

        this->address = {};
        this->address.sun_family = AF_UNIX;
        
        if(path.size() >= sizeof(this->address.sun_path) - 1) {
            throw std::runtime_error("unix path too long");
        }
        
        strncpy(address.sun_path, path.data(), sizeof(address.sun_path) - 1);
        address.sun_path[sizeof(address.sun_path) - 1] = '\0';
        
        this->length = sizeof(this->address);
    }

    void* UnixAddress::data() {
        return &this->address;
    }

    const void* UnixAddress::data() const {
        return &this->address;
    }

    socklen_t& UnixAddress::size() {
        return this->length;
    }

    int UnixAddress::family() const {
        return AF_UNIX;
    }
};
