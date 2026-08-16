#include "client.h"

#include <queue>
#include <string>
#include <string.h>
#include <signal.h> 
#include <iostream>
#include <stdexcept>
#include <sys/ipc.h>
#include <sys/msg.h> 

using error = std::runtime_error;

std::queue<Message> message_queue {};
int message_queue_id { -1 };
::pthread_mutex_t lock {};
bool is_running { true };

void* recv(void* arg) {
    while(is_running) {
        Message msg {};
        const ssize_t result { ::msgrcv(message_queue_id, &msg, sizeof(msg.msgBuf), 4, MSG_NOERROR) };

        if (result == -1) {
            if (errno == EINTR) {
                continue;
            }
            
            if (errno == EIDRM || errno == EINVAL) {
                break;
            }
            
            std::cerr << "msgrcv: " << ::strerror(errno) << '\n';
            continue;
        }

        ::pthread_mutex_lock(&lock);
            message_queue.push(msg);
        ::pthread_mutex_unlock(&lock);
    }

    ::pthread_exit(nullptr);
    return nullptr;
}


int main() {
    // Setup Signals
    struct sigaction signalHandler {
        [](const int signal) -> void {
            switch(signal) {
                case SIGINT:
                    is_running = false;
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

    std::cout << "Initializing Message Queue\n";
    const key_t key { ::ftok("serverclient", 65) };
    if(key == -1) { error("ftok()"); }

    message_queue_id = ::msgget(key, IPC_CREAT | 0666);
    if(message_queue_id == -1) { ::error("msgget()"); }

    std::cout << "[Server]: queue id: " << message_queue_id << "\n";

    ::pthread_mutex_init(&lock, nullptr);
    ::pthread_t threadId;
    
    const int result { ::pthread_create(&threadId, nullptr, recv, nullptr) };
    if(result != 0) {
        is_running = false;
        std::cerr << ::strerror(errno) << "\n";

        return -1;
    }

    std::cout << "[Server]: Message Queue Setup Successfully"
        "\n[Server]: Processing Clients\n";
    
    while(is_running) {
        Message recvMsg {};
        bool hasMessage = false;

        ::pthread_mutex_lock(&lock);

        if (!message_queue.empty()) {
            recvMsg = message_queue.front();
            message_queue.pop();
            hasMessage = true;
        }

        ::pthread_mutex_unlock(&lock);

        if (!hasMessage) {
            ::sleep(1000);
            continue;
        }

        std::cout << "[Server] got request: " << recvMsg.msgBuf.buf << '\n';

        Message sendMessage {};
        sendMessage.mtype = recvMsg.msgBuf.dest;
        sendMessage.msgBuf.source = recvMsg.msgBuf.source;
        sendMessage.msgBuf.dest = recvMsg.msgBuf.dest;

        ::strncpy( sendMessage.msgBuf.buf, recvMsg.msgBuf.buf, sizeof(sendMessage.msgBuf.buf) );
        sendMessage.msgBuf.buf[ sizeof(sendMessage.msgBuf.buf) - 1 ] = '\0';

        if (::msgsnd( message_queue_id, &sendMessage, sizeof(sendMessage.msgBuf), 0 ) == -1) {
            std::cerr << "msgsnd: " << ::strerror(errno) << '\n';
        }
    }

    std::cout << "[Server]: Closing Message Queue\n";

    constexpr int maxNumberOfClients { 3 };
    for (long client = 1; client <= maxNumberOfClients; ++client) {
        Message quitMessage {};

        quitMessage.mtype = client;
        quitMessage.msgBuf.source = 4;
        quitMessage.msgBuf.dest = client;

        ::strncpy( quitMessage.msgBuf.buf, "Quit", sizeof(quitMessage.msgBuf.buf) );

        if (::msgsnd( message_queue_id, &quitMessage, sizeof(quitMessage.msgBuf), 0) == -1) {
            std::cerr << "Could not send Quit to client " << client 
                << ": " << ::strerror(errno) << '\n';
        }
    }

    ::msgctl(message_queue_id, IPC_RMID, nullptr);
    ::pthread_join(threadId, nullptr);
    ::pthread_mutex_destroy(&lock);
    
    std::cout << "[Server]: Shutdown complete\n";
    return EXIT_SUCCESS;
}