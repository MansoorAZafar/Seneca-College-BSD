#include <array>
#include <string>
#include <iostream>
#include <unistd.h>
#include <type_traits>
#include "utility/logger.hpp"
#include "server_builder.hpp"
#include "sock_server_builder.hpp"
#include "dgram_server_builder.hpp"
#include "core/address/address.hpp"
#include "core/address/unix_address.hpp"
#include "core/address/inet_address.hpp"
#include "core/config/server_client_config.hpp"
#define MAX_BUFFER_SIZE 1024

using namespace L6;
int main(int argc, char** argv) {
    const Args args { init(argc, argv) };   
    const std::string_view operation { args.find(to_string(ServerArgs::DOMAIN))->second    };
    const std::string_view logLevel  { args.find(to_string(ServerArgs::LOG_LEVEL))->second };

    Logger& instance { Logger::getInstance() };
    instance.setLogFile("server.log");
    instance.setConfiguration(from_string(logLevel));
    instance.logHeader();

    std::cout << "Starting up: " << operation << " Server\n";

    const char* unixLinkAddress { "/tmp/lab6_mz" };
    const bool is_unix { operation == "stream" || operation == "dgram" };
    const std::array<std::pair<const std::string, const std::string>, MAX_NUM_COMMANDS> instructions {{
        {"Pid"  , "This client has pid <%s>\n"},
        {"Sleep", "Client sleep status: %s\n" },
        {"Quit" , "" },
    }};
    
    InetAddress inet_addr("127.0.0.1", 8080);
    UnixAddress unix_addr(unixLinkAddress);
    
    ServerBuilder* server {nullptr};
    Address* addr {nullptr};
    
    if(is_unix) {
        ::unlink(unixLinkAddress);
        addr = &unix_addr;
    } else addr = &inet_addr;

    if(operation == "tcp") {
        l6_info("Using AF_INET Sock");        
        server = new TCPServerBuilder{};
    } else if (operation == "udp") {
        l6_info("Using AF_INET DGRAM");
        server = new UDPServerBuilder{};
    } else if (operation == "dgram") {
        l6_info("Using AF_UNIX DGRAM");
        server = new DgramServerBuilder{};
    } else {
        l6_info("Using AF_UNIX Sock");
        server = new StreamServerBuilder{};
    }

    server->handleClient(*addr, instructions);

    if(server != nullptr) delete server;
    if(is_unix) ::unlink(unixLinkAddress);

    return 0;
}