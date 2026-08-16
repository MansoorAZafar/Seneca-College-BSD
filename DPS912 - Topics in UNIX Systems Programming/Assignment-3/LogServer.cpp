#include "Commons.hpp"
#include <signal.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <system_error>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unordered_set>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <cstring>

namespace AS3 {
    sig_atomic_t is_running { 1 };
    pthread_t thread_id {};

    sockaddr_in client_address {};
    socklen_t client_length { sizeof(client_address) };

    Mutex mutex {};

    constexpr int BUF_LEN { 4096 };
    constexpr const char* const LOG_FILE { "server.log" };
    const int file_fd { ::open(LOG_FILE, O_RDWR | O_CREAT, 0666) };
};

void* recv(void* args) {    
    int fd { *(static_cast<int*>(args)) };

    char buffer[AS3::BUF_LEN] {};
    while(AS3::is_running) {
        AS3::mutex.lock();
        const ssize_t bytes_read { ::recvfrom(
            fd, 
            buffer, 
            AS3::BUF_LEN - 1, 
            0, 
            reinterpret_cast<sockaddr*>(&AS3::client_address), 
            &AS3::client_length
        )};
        AS3::mutex.unlock();

        if(bytes_read == -1) {
            if(errno == EAGAIN || errno == EWOULDBLOCK) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            std::cerr << "recvfrom error: " << strerror(errno) << '\n';
            continue;
        }
        
        buffer[bytes_read] = '\0';

        AS3::mutex.lock();
        ::write(AS3::file_fd, buffer, ::strlen(buffer));
        AS3::mutex.unlock();
    }

    ::pthread_exit(nullptr);
}

int main() {
    const std::unordered_set<std::string> allowed_log_level_inputs { "debug", "warning", "error", "critical" };

    std::cout << "[Server]: Setting up Signals\n";
    struct sigaction signalHandler {
        [](const int signal) -> void {
            if(signal == SIGINT) AS3::is_running = 0;
        },
        {},
        0,
        nullptr
    };

    ::sigaction(SIGINT, &signalHandler, NULL);
    std::cout << "[Server]: Signals Setup SUccessfully\n";
    int fd { ::socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0) };

    sockaddr_in server_address { AF_INET, ::htons(AS3::SERVER_PORT), ::htonl(INADDR_ANY) };
    socklen_t length { sizeof(server_address) };

    if(::bind(fd, reinterpret_cast<sockaddr*>(&server_address), length) == -1) {
        ::close(fd);
        throw std::system_error(errno, std::system_category(), "bind");
    }
    
    AS3::mutex.init();
    const int result { ::pthread_create(&AS3::thread_id, nullptr, recv, &fd) };
    
    if(result != 0) throw std::system_error(errno, std::system_category(), "pthread_create");
    std::cout << "[UDP Server] Listening on port <" << AS3::SERVER_PORT << ">\n";

    std::string input {};
    while(AS3::is_running) {
        std::cout << "Select your choice\n"
            "\t1: Set The Log Level\n"
            "\t2: Dump The Log File\n"
            "\t0: Shut Down\n> ";

        std::getline(std::cin, input);
        std::istringstream ss(input);

        int choice;
        if(ss >> choice && (choice < 3 && choice >= 0)) {

            switch(choice) {
                case 1: {
                    std::cout << "Enter a LogLevel: (DEBUG, WARNING, ERROR, CRITICAL)\n> ";
                    std::getline(std::cin, input);

                    std::transform(input.begin(), input.end(), input.begin(), [](const unsigned char ch) {
                        return std::tolower(ch);
                    });

                    if(allowed_log_level_inputs.find(input) == allowed_log_level_inputs.end()) continue;
                    const std::string message { "Set Log Level=<" + input + ">" };
                    
                    AS3::mutex.lock();
                    ::sendto(
                        fd, 
                        message.data(), 
                        message.size(), 
                        0, 
                        reinterpret_cast<sockaddr*>(&AS3::client_address), 
                        AS3::client_length
                    );
                    AS3::mutex.unlock();
                    break;
                }
                case 2: {
                    AS3::mutex.lock();
                    ::lseek(AS3::file_fd, 0, SEEK_SET);
                    char buffer[AS3::BUF_LEN] {};

                    ssize_t bytes_read {};
                    while((bytes_read = ::read(AS3::file_fd, buffer, AS3::BUF_LEN)) > 0) {
                        ::write(STDOUT_FILENO, buffer, bytes_read);
                    }
                    
                    AS3::mutex.unlock();

                    std::cout << "Press any key to continue\n";
                    std::cin.get();

                    break;
                }
                default: {
                    AS3::mutex.lock();
                    AS3::is_running = false;
                    AS3::mutex.unlock();
                }
            }

        } else {
            std::cerr << "[ERROR]: Invalid selection\n";
        }
    }

    AS3::mutex.cleanup();
    ::shutdown(fd, SHUT_RDWR);
    ::pthread_join(AS3::thread_id, nullptr);

    ::close(AS3::file_fd);
}