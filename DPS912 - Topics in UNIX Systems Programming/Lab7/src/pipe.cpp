#include "lab7/pipe.hpp"
namespace L7 {
    // Pipe createPipe() {
    //     int fds[2] {};
    //     if(::pipe(fds) == -1) throw std::runtime_error("pipe()");

    //     return {
    //         FileDescriptor(fds[0]),
    //         FileDescriptor(fds[1])
    //     };
    // }

    Pipe::Pipe() {
        int fds[2] {};
        if(::pipe(fds) == -1) throw std::runtime_error("pipe()");

        std::cerr << "[PIPE] read=" << fds[0]
              << " write=" << fds[1] << '\n';

        this->read = std::move(FileDescriptor(fds[0]));
        this->write = std::move(FileDescriptor(fds[1]));
    }
};