#include <cstdio>
#include <string>
#include <vector>
#include <csignal>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>
#include "WorkerArgs.hpp"
#include <bits/signum-arch.h>

// Declarations
struct Args;

void mz_signal_handler(int sig);
void mz_setup_signals();
void mz_log_event(const char* message);
void spawn_workers(pid_t* children, const int n, const AS1::WorkerAction& action);
Args init(int argc, char** argv);
void wait_for_tasks();


struct Args {
    pid_t* children;
    const int size;
};

void mz_signal_handler(int sig) {
    if (sig == SIGUSR1) {
        mz_log_event("[WARNING] Worker Memory Limit Exceeded\n");
        printf("Worker process exceeded memory limit!\n");
    } else if (sig == SIGUSR2) {
        mz_log_event("[INFO] Worker Completed its task\n");
        printf("Worker process completed its task.\n");
    }
}
 
void mz_setup_signals() {
    signal(SIGUSR1, mz_signal_handler);
    signal(SIGUSR2, mz_signal_handler);
}

void mz_log_event(const char *message) {
    int fd = open("syslog.log", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd < 0) {
        perror("Log file open failed");
        return;
    }
 
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
 
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("File lock failed");
        close(fd);
        return;
    }
 
    write(fd, message, strlen(message));
 
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
 
    close(fd);
}

void spawn_workers(pid_t* children, const int n, const AS1::WorkerAction& action) {
    std::vector<int> sizes(n);
    const int parentPid { getpid() };

    if(action == AS1::WorkerAction::WORKER_CREATE) {
        for(int i = 0; i < n; ++i) {
            std::cout << "\nEnter file size for Worker " << std::to_string(i + 1) << " (MB)\n> ";
            std::cin >> sizes[i];
        }
    }

    for(int i = 0; i < n; ++i) {
        children[i] = fork();
        if( children[i] == 0 ) {            
            const int mb { sizes[i] };
            const int workerNumber { i + 1 };
            const char* executable = "./out/worker";

            const AS1::WorkerArgs args { mb, workerNumber, parentPid, executable, action };
            std::array<std::string, 9> formattedArguments = AS1::WorkerArgs::create(args);
            
            std::array<char*, 10> rawCharArguments;
            for(size_t j = 0; j < formattedArguments.size(); ++j) rawCharArguments[j] = formattedArguments[j].data();
            rawCharArguments[formattedArguments.size()] = nullptr;
            
            execvp(executable, rawCharArguments.data());
            perror("execvp");

            std::cout << "\033[31mthis message should not appear. What should I do if it does...?\033[0m\n";
            std::cout << "[ERROR]: child:main pid: " << getpid() << " I should not get here\n";
            std::cout << strerror(errno) << "\n";
            
            exit(1);
        }
    }

    std::cout << "\n";
}

Args init(int argc, char** argv) {
    mz_setup_signals();

    constexpr int DEFAULT_NUMBER_PROCESSES { 3 };
    const int NUM_PROCESSES { argc == 2 ? std::stoi(argv[1]) : DEFAULT_NUMBER_PROCESSES };
    
    pid_t* children = new int[NUM_PROCESSES];
    return { children, NUM_PROCESSES };
}

void wait_for_tasks() {
    int status { -1 };
    pid_t pid { 0 };

    while( pid >= 0) {
        pid = wait(&status);
        // LOG("parent status: %d. the child pid: %d has finished\n", status, pid);

        if(WIFEXITED(status)) {
            const int exit_code { WEXITSTATUS(status) };
            if(exit_code != 0) {
                std::cerr << "[ERROR] Child: " << pid << " finished: BAD (failed with bad exit code): " << exit_code << "\n";
            }
        } else if (WIFSIGNALED(status)) {
            const int signal_num { WTERMSIG(status) };
            std::cout << "[ERROR] Child: " << pid << " finished: BAD (Killed by Signal): " << signal_num << "\n";
        }        
    }
}

int main(int argc, char** argv) {
    auto [children, n] { init(argc, argv) };
    
    spawn_workers(children, n, AS1::WorkerAction::WORKER_CREATE);
    wait_for_tasks();
    std::cout << "Binary files created.\n";

    spawn_workers(children, n, AS1::WorkerAction::WORKER_READ);
    wait_for_tasks();

    delete[] children;
    return 0;
}