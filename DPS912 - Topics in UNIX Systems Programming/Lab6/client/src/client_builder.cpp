#include "client_builder.hpp"

namespace L6 {
    void ClientBuilder::process(Socket* _client, Address* _server) {
        this->client = _client;
        this->server = _server;

        this->initConnection();
        std::array<char, MAX_BUFFER_SIZE> buffer;
        
        bool told_to_quit { false };
        while(!told_to_quit) {
            const ssize_t bytesRead { this->read(buffer.data(), buffer.size() - 1) };
            buffer[bytesRead] = '\0';

            const std::string_view operation { buffer.data() };
            std::cout << "operation: " << operation << "\n";

            std::string message {};
            if( operation.compare("Pid") == 0 ) {
                const pid_t pid { getpid() };
                message = std::to_string(pid);
            } else if ( operation.compare("Sleep") == 0 ) {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                message = "Done";
            } else if( operation.compare("Quit") == 0 ) {
                std::cout << "Quitting loop\n";

                message = "Acknowledged, Now Quitting";
                told_to_quit = true;
            }

            this->write(message);
            std::cout << "Client read command: " << buffer.data() << "\n";
        }
    }

};