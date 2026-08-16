#include "lab7/file_descriptor.hpp"
#include "lab7/pipe.hpp"
#include "lab7/util.hpp"
#include <sys/wait.h>
#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <cerrno>

int main(int argc, char** argv) {
    if(argc < 3) throw std::runtime_error("Must be at least 3 args, ./lab7.exe <arg1> <arg2> ...\n");
    const int NUMBER_OF_ARGS { argc - 1 };
    
    // Exclude the filename
    char** args { argv + 1 };
    int index { 0 };

    // Represents the file descriptor that the input wants to read FROM
    // Each operation wants to read from the previous' one
    L7::FileDescriptor read {};

    // N - 1 pipes
    // suppose we have N operations
    // there will be N - 1 connections
    // ls --> grep --> sort --> uniq
    // 3 connections, ls to grep, grep to sort and finally sort to uniq
    // So we have N - 1 connections
    for(; index < NUMBER_OF_ARGS - 1; ++index) {
        L7::Pipe pipe { };

        const pid_t pid { ::fork() };
        if(pid == 0) {
            std::cerr << "[CHILD " << getpid()
                    << "] read=" << int(read)
                    << " write=" << int(pipe.write)
                    << " pipe.read=" << int(pipe.read)
                    << '\n';

            if(read != -1) {
                if (fcntl(read, F_GETFD) == -1) perror("read before dup2");
                ::dup2(read, STDIN_FILENO);
                ::close(read);
            }

            
            if(pipe.write != STDOUT_FILENO) {
                if (fcntl(pipe.write, F_GETFD) == -1) perror("pipe.write before dup2");
                ::dup2(pipe.write, STDOUT_FILENO);
                ::close(pipe.write);
            }

            ::close(pipe.read);
            L7::runCommand(args[index]);
            std::cerr << "[ERROR]: execvp() failed\n";
            exit(EXIT_FAILURE);
        }

        // Move to the next connection
        read = std::move(pipe.read);
        std::cerr << "[PARENT] new read=" << int(read)
          << " pipe.read=" << int(pipe.read)
          << " pipe.write=" << int(pipe.write)
          << '\n';
    }

    //Process final operation
    const pid_t finalPid { ::fork() };
    if(finalPid == 0) {
        if(read != -1) {
            ::dup2(read, STDIN_FILENO);
            ::close(read);
        }

        L7::runCommand(args[index]);
        std::cerr << "[ERROR] execlp() failed\n";
        exit(EXIT_FAILURE);     
    }

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

    if(read != STDIN_FILENO) ::close(read);
    return 0;
}