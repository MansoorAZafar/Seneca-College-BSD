#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdexcept>
#include <vector>
#include "WorkerArgs.hpp"
 
void mz_generate_binary_file(const char *filename, int size_mb) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("File creation failed");
        exit(1);
    }
 
    char buffer[1024 * 1024]; // 1MB buffer
    memset(buffer, 'X', sizeof(buffer)); // Fill with dummy data
 
    for (int i = 0; i < size_mb; i++) {
        write(fd, buffer, sizeof(buffer));
    }
 
    close(fd);
}

void mz_worker_process(const char *filename, pid_t parent_pid) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Worker: Failed to open file");
        exit(1);
    }
 
    char buffer[4096]; // 4KB buffer
    ssize_t bytes_read;
    int mem_usage = 0;

    std::vector<char> accumulator(4096);
    bool informedUser{ false };
 
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        accumulator.insert(accumulator.end(), buffer, buffer + bytes_read);

        FILE *status_file = fopen("/proc/self/status", "r");
        if (!status_file) {
            perror("Failed to open /proc/self/status");
            exit(1);
        }
 
        char line[256];
        while (fgets(line, sizeof(line), status_file)) {
            if (strncmp(line, "VmRSS:", 6) == 0) {
                sscanf(line + 6, "%d", &mem_usage);
                break;
            }
        }
        fclose(status_file);
 
        if (mem_usage > 50000 && !informedUser) {
            kill(parent_pid, SIGUSR1);
            informedUser = true;
        }
    }
 
    close(fd);
    printf("Worker completed: %s\n", filename);

    kill(parent_pid, SIGUSR2);
    // exit(0);
}

/**
 * argv: 
 *  ./out/worker --mb [int] --worker [worker num] --parent [parent pid] --action [create/read]
 */
int main(int argc, char** argv) {
    const auto [ mb, worker, parentPid, _, action ] { AS1::WorkerArgs::parse(argc, argv) };
    const std::string filename { "worker" + std::to_string(worker) + ".bin" };

    switch(action) {
        case AS1::WorkerAction::WORKER_CREATE:
            mz_generate_binary_file(filename.c_str(), mb);
            break;
        case AS1::WorkerAction::WORKER_READ:
            mz_worker_process(filename.c_str(), parentPid);
            break;
    }
 
    return 0;
}