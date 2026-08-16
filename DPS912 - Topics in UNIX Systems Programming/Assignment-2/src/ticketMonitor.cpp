#include "logger.hpp"
#include "fifo.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

int main() {
    mz::setConfiguration(mz::LogLevel::DEBUG);
    mz::setLogFile("monitor.log");
    mz::logHeader();
    
    std::cout << "Beginning Monitor\n";
    constexpr const char* mainServerFIFO { "/tmp/ticket_notifications.fifo" };
    std::unordered_map<std::string, AS2::Fifo> fifos{};    

    fifos.try_emplace(mainServerFIFO, mainServerFIFO, O_RDONLY);
    const int serverFd {fifos[mainServerFIFO].fd()};

    std::cout << "Waiting for notifications\n";
    bool running {true};
    while(running) {
        fd_set readSet{};
        FD_ZERO(&readSet);

        int maxFd { -1 };
        for(auto& [_, fifo] : fifos) {
            FD_SET(fifo.fd(), &readSet);
            maxFd = std::max(maxFd, fifo.fd());
        }

        int ready = ::select(maxFd + 1, &readSet, nullptr, nullptr, nullptr);
        if(ready < 0) {
            std::cerr << "select()\n";
            mz::warn("[MAIN]: select() failed\n");

            break;
        }

        std::vector<std::string> newFifos;
        for(auto& [_, it] : fifos) {
            if(FD_ISSET(it.fd(), &readSet)) {
                std::string input = it.read();
                
                mz::info("Read: " + input);
                std::cout << input << "\n";
                
                if(it.fd() == serverFd && (input == "[NOTIFY] Server Shutting Down" || input.empty())) {
                    mz::debug("Closing Ticket Monitor");
                    running = false;
                    
                    break;
                } else if (it.fd() == serverFd) {
                    newFifos.push_back(input);
                }

            }
        }

        for (const auto& path : newFifos) {
            fifos.try_emplace(path, path.c_str(), O_RDONLY);
        }
    }

    return 0;
}