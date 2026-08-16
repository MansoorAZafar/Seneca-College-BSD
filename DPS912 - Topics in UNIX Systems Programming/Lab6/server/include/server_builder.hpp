#ifndef L6_SERVER_BUILDER_HPP
#define L6_SERVER_BUILDER_HPP

#include "core/address/address.hpp"
#include "utility/logger.hpp"

#include <string>
#include <array>
#include <iostream>
#include <string_view>

namespace L6 {
    constexpr int MAX_NUM_COMMANDS { 3 };
    using Command = std::array<std::pair<const std::string, const std::string>, MAX_NUM_COMMANDS>;

    class ServerBuilder {
    protected:
        virtual void initServer(Address& address) = 0;
        virtual void initConnection() = 0;
        virtual void write(const std::string& message) = 0;
        virtual ssize_t read(void* buf, const size_t& n) = 0;

    public:
        ServerBuilder() = default;
        virtual ~ServerBuilder() = default;

        void handleClient(Address& address, const Command& commands);
    };
};

#endif