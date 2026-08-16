#ifndef L7_PIPE_HPP
#define L7_PIPE_HPP

#include <unistd.h>
#include <stdexcept>
#include "lab7/file_descriptor.hpp"

namespace L7 {
    struct Pipe {
        FileDescriptor read {};
        FileDescriptor write {};

        Pipe();
    };

    // Pipe createPipe();
};
#endif