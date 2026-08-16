#ifndef L6_CLIENT_BUILDER_HPP
#define L6_CLIENT_BUILDER_HPP

#include "core/address/address.hpp"
#include "core/socket/socket.hpp"
#include <chrono>
#include <array>
#include <thread>
#include <string>
#include <unistd.h>
#include <iostream>

namespace L6 {
    constexpr int MAX_BUFFER_SIZE { 1024 };

    class ClientBuilder {
    protected:
        Socket* client;
        Address* server;

        virtual void initConnection() = 0;
        virtual void write(const std::string& message) = 0;
        virtual ssize_t read(void* buf, const size_t& n) = 0;

    public:
        ClientBuilder() = default;
        virtual ~ClientBuilder() = default;

        void process(Socket* _client, Address* _server);
    };
};
#endif