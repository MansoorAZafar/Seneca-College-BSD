#include <netinet/in.h>
#include <sys/socket.h>
#include <system_error>
#include <string_view>
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <queue>

namespace L9 {

    bool is_running { true };
    pthread_mutex_t lock{};
    std::queue<std::string> message_queue{};

    struct InetAddress {
        sockaddr_in address {};
        socklen_t length { sizeof(address) };
    };

    InetAddress init_tcp_address(const std::string_view& ip, const uint16_t& port) {
        InetAddress iaddr { };

        iaddr.address.sin_family = AF_INET;
        iaddr.address.sin_port = ::htons(port);
        
        iaddr.length = sizeof(iaddr.address);
        if(::inet_pton(AF_INET, ip.data(), static_cast<void*>(&iaddr.address.sin_addr)) != 1) {
            throw std::system_error(errno, std::system_category(), "inet_pton");
        }

        return iaddr;
    }

    struct Socket {
        int fd { -1 };
        
        Socket(int _fd) : fd(_fd) { if(!this->valid()) throw std::system_error(errno, std::system_category(), "socket"); }

        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        Socket(Socket&& other) { *this = std::move(other); }
        Socket& operator=(Socket&& other) {
            if(this != &other) {
                if(this->valid()) ::close(this->fd);
                
                this->fd = std::exchange(other.fd, -1);
            }

            return *this;
        }

        inline bool valid() const { return this->fd != -1; };
        ~Socket() { if(this->valid()) ::close(this->fd); }
    };

    struct Listener { Socket socket; };
    struct Connection { Socket socket; InetAddress client_address; };

    template <class T = Connection>
    struct Optional {
        union { char placeholder_; T val_; };
        bool engaged_;

        Optional(): engaged_(false), placeholder_(0) {}
        Optional(const T& t) : engaged_(true), val_(t) {}
        Optional(T&& val) : val_(std::move(val)), engaged_(true) {}

        Optional(Optional&& other): engaged_(other.engaged_) {
            if(this->engaged_) { 
                new (&val_) T(std::move(other.val_));
                other.engaged_ = false;
            };
        }

        Optional& operator=(Optional&& other) {
            if(this != &other) {
                if(this->engaged_) this->val_.~T();
                
                this->engaged_ = other.engaged_;
                if(this->engaged_) { 
                    new (&val_) T(std::move(other.val_));
                    other.engaged_ = false;
                }
            }

            return *this;
        }

        Optional(const Optional&) = delete;
        Optional& operator=(const Optional&) = delete;

        Optional& operator=(const T& val) {
            if(this->engaged_) {
                this->val_ = val;
            } else {
                new (&val_) T(val); // Placement new, NOT A HEAP ALLOCATION
                this->engaged_ = true;
            }

            return *this;
        }

        Optional& operator=(T&& val) {
            if(this->engaged_) {
                this->val_ = std::move(val);
            } else {
                new (&val_) T(std::move(val));
                this->engaged_ = true;
            }

            return *this;
        }

        ~Optional() {
            if(this->engaged_) this->val_.~T(); 
        }

        bool has_value() const { return this->engaged_; }
        T& operator*() { return this->val_; };
    };

    inline Listener tcp_socket() { return { ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0) }; }
    void init_server(Listener& server, InetAddress& addr, const int backlog = 5) {
        if(::bind(server.socket.fd, reinterpret_cast<sockaddr*>(&addr.address), addr.length) == -1) {
            throw std::system_error(errno, std::system_category(), "bind");
        }

        if(::listen(server.socket.fd, backlog) == -1) {
            throw std::system_error(errno, std::system_category(), "listen");
        }
    }

    inline Optional<Connection> accept(const Listener& server) { 
        Optional conn{};

        InetAddress client_address {};
        const int client_fd { ::accept(server.socket.fd, reinterpret_cast<sockaddr*>(&client_address.address), &client_address.length) };
        if(client_fd == -1 && (errno != EAGAIN && errno != EWOULDBLOCK)) { 
            throw std::system_error(errno, std::system_category(), "accept");                 
        } else if(client_fd != -1) {
            conn = Connection{ Socket(client_fd), client_address };             
        }

        return conn;
    };

    inline ssize_t write(const int fd, const std::string_view& message){ return ::write(fd, message.data(), message.size()); }
    void* recv_func(void *arg) {
        constexpr int BUF_LEN=4096;
        int fd = *(int *)arg;
        char buf[BUF_LEN];
        
        ::timeval timeout{};
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        
        if(::setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
            std::cerr << "setsockopt failed: " << std::strerror(errno) << '\n';
            
            ::pthread_exit(NULL);
            return nullptr;
        }

        while(L9::is_running) {
            const ssize_t len { ::read(fd, buf, BUF_LEN) };
            
            if(len > 0) {
                ::pthread_mutex_lock(&L9::lock);
                L9::message_queue.push(std::string(buf));
                ::pthread_mutex_unlock(&L9::lock);
            } else if(len == 0) { break; }
            else {
                if(errno == EAGAIN || errno == EWOULDBLOCK) {
                    continue;
                } else if (errno == EINTR) break;

                std::cerr << "[SERVER]: read failed: " << std::strerror(errno) << "\n";
                break; 
            }
        }

        ::pthread_exit(NULL);
    }
}


int main(int argc, char** argv) {
    if(argc != 2) throw std::runtime_error("usage: server <port number>");
    uint16_t port {};

    std::cout << "[Server]: Parsing Port from **argv\n";
    try {
        port = std::stoi(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "[Server]: Setting up Signals\n";
    struct sigaction signalHandler {
        [](const int signal) -> void {
            switch(signal) {
                case SIGINT:
                    L9::is_running = false;
                    break;
                default: 
                    std::cerr << "[SIGNAL HANLDER]: Unknown signal: " << signal << "\n";
            }
        },       // sa_handler
        {},      // sa_mask 
        0,       // sa_flags
        nullptr  // sa_restorer
    };

    ::sigaction(SIGINT, &signalHandler, NULL);
    std::cout << "[Server]: Signals Setup Successfully\n";


    L9::InetAddress address { L9::init_tcp_address("127.0.0.1", port) };
    L9::Listener server { L9::tcp_socket() };
    
    L9::init_server(server, address);
    std::cout << "[Server]: Server listening on: 127.0.0.1:" << port << "\n";

    constexpr int NUMBER_OF_CLIENTS { 3 };
    std::vector<L9::Optional<L9::Connection>> connections{};
    std::vector<pthread_t> threads{};

    connections.reserve(NUMBER_OF_CLIENTS);
    threads.reserve(NUMBER_OF_CLIENTS);

    ::pthread_mutex_init(&L9::lock, nullptr);

    int number_of_accepted_clients { 0 };
    while(L9::is_running) {
        if(number_of_accepted_clients < NUMBER_OF_CLIENTS) {
            L9::Optional<L9::Connection> conn { L9::accept(server) };
            if(conn.has_value()) {
                std::cout << "[Server]: Client Connected. Fd: " << (*conn).socket.fd << "\n";
                connections.emplace_back(std::move(conn));
                int* fd { &(*connections.back()).socket.fd };

                pthread_t thread_id {};
                const int result { ::pthread_create(&thread_id, nullptr, L9::recv_func, fd) };
                if(result != 0) {
                    std::cerr << ::strerror(errno) << "\n";
                    continue;
                }

                threads.push_back(thread_id);
            } else {
                std::cout << "[Server]: No client waiting\n";
            }
        }

        // LOCK
        ::pthread_mutex_lock(&L9::lock);
        int count { 1 };
        // drain the queue each time
        while(L9::message_queue.size() > 0) {
            const std::string message { L9::message_queue.front() };
            L9::message_queue.pop();

            std::cout << "[Message Queue #" << count++ << "]: " << message << "\n"; 
        }

        // UNLOCK
        ::pthread_mutex_unlock(&L9::lock);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\n[Server]: Cleaning up Connections\n";
    for(L9::Optional<L9::Connection>& conn : connections) { L9::write((*conn).socket.fd, "Quit"); }
    for(const pthread_t thread_id : threads) { ::pthread_join(thread_id, nullptr); }
    ::pthread_mutex_destroy(&L9::lock);

    std::cout << "[Server]: Press <ENTER> To End The Program\n";
    std::cin.get();
 
    return EXIT_SUCCESS;
}