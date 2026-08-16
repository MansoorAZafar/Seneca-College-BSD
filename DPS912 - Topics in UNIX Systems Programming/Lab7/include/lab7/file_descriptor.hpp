#ifndef L7_FILE_DESCRIPTOR_HPP
#define L7_FILE_DESCRIPTOR_HPP
#include <unistd.h>
#include <utility>
#include <iostream>

namespace L7 {
    class FileDescriptor {
    private:
        int m_fd { -1 };
    public:
        FileDescriptor() = default;
        explicit FileDescriptor(const int fd);

        FileDescriptor(const FileDescriptor&) = delete;
        FileDescriptor& operator=(const FileDescriptor&) = delete;
        FileDescriptor& operator=(FileDescriptor&& other);
        FileDescriptor(FileDescriptor&& other);

        int get() const;
        int release();
        
        operator int() const;
        ~FileDescriptor();
    };
};

#endif