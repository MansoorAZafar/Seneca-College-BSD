#include "server_builder.hpp"

namespace L6 {
    void ServerBuilder::handleClient(Address& address, const Command& commands) {
        this->initServer(address);
        
        int instructionIndex { 0 };
        bool flag {true};

        while(flag) {
            try {
                this->initConnection();
                std::array<char, 1024> buffer;

                while(flag) {
                    const auto [command, printMsg] { commands[instructionIndex++] };
                    
                    const std::string log_msg{"Using Command: " + command};
                    l6_info(log_msg);

                    std::cout << "Using Command: [" << command.data() << "]\n";
                    
                    this->write(command);
                    const ssize_t bytesRead { this->read(buffer.data(), buffer.size() -1) };

                    if(bytesRead == -1) {
                        std::cerr << "read()\n";
                        l6_warn("read()");
                        
                        break;
                    }

                    if(bytesRead == 0) {
                        std::cout << "Client disconnected\n";
                        l6_info("Client disconnected");

                        break;
                    }

                    buffer[bytesRead] = '\0';
                    printf(printMsg.data(), buffer.data());

                    if(command.compare("Quit") == 0) {
                        flag = false;
                        break;
                    }
                }

                instructionIndex = 0;
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << "\n";
                l6_warn(e.what());

                continue;
            }
        }
    }
};