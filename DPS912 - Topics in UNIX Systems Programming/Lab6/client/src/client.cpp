#include <array>
#include <thread>
#include <chrono>
#include <string_view>
#include "utility/logger.hpp"
#include "client_builder.hpp"
#include "core/socket/socket.hpp"
#include "core/socket/socket.hpp"
#include "sock_client_builder.hpp"
#include "dgram_client_builder.hpp"
#include "core/address/address.hpp"
#include "core/address/unix_address.hpp"
#include "core/socket/stream_socket.hpp"
#include "core/address/inet_address.hpp"
#include "core/socket/datagram_socket.hpp"
#include "core/config/server_client_config.hpp"

using namespace L6;
int main(int argc, char** argv) {
    const Args args { init(argc, argv) };   
    const std::string_view operation { args.find(to_string(ServerArgs::DOMAIN))->second    };
    const std::string_view logLevel  { args.find(to_string(ServerArgs::LOG_LEVEL))->second };

    Logger& instance { Logger::getInstance() };
    instance.setLogFile("client.log");
    instance.setConfiguration(from_string(logLevel));
    instance.logHeader();

    std::cout << "Starting up: " << operation << " Client\n";

    const char* clientUnixLinkAddress { "/tmp/client" };
    const char* serverUnixLinkAddress { "/tmp/lab6_mz" };
    const bool is_unix { operation == "stream" || operation == "dgram" };


    InetAddress server_inet_addr("127.0.0.1", 8080);
    
    UnixAddress server_unix_addr{serverUnixLinkAddress};
    UnixAddress client_unix_addr{clientUnixLinkAddress};

    Socket* socket {nullptr};
    Address* server {nullptr};
    ClientBuilder* client {nullptr};

    
    if(is_unix) {
        ::unlink(clientUnixLinkAddress);
        server = &server_unix_addr;
    } else {
        server = &server_inet_addr;
    }


    if (operation == "tcp") {
        l6_info("Using AF_INET TCP");

        socket = new StreamSocket { AF_INET, SOCK_STREAM };
        client = new TCPClientBuilder();
    } else if (operation == "udp") {
        l6_info("Using AF_UNIX UDP");
        
        socket = new DatagramSocket { AF_INET, SOCK_DGRAM };
        client = new UDPClientBuilder();
    } else if (operation == "dgram") {
        l6_info("Using AF_UNIX DGRAM");

        socket = new DatagramSocket { AF_UNIX, SOCK_DGRAM };
        socket->bind(client_unix_addr);

        client = new DgramClientBuilder();
    } else {
        l6_info("Using AF_UNIX Sock");

        socket = new StreamSocket { AF_UNIX, SOCK_STREAM };
        client = new StreamClientBuilder();
    }

    client->process(socket, server);

    if(socket != nullptr) delete socket;
    if(client != nullptr) delete client;

    if(is_unix) ::unlink(clientUnixLinkAddress);
    return 0;
}