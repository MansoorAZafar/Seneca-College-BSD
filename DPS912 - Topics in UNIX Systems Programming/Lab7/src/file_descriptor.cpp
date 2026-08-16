#include "lab7/file_descriptor.hpp"
namespace L7 {
    FileDescriptor::FileDescriptor(const int fd)
        : m_fd(fd) {}
  
    int FileDescriptor::get() const {
        return this->m_fd;
    }

    FileDescriptor::operator int() const {
        return this->m_fd;
    }

    int FileDescriptor::release() {
        const int tmp { this->m_fd };
        this->m_fd = -1;

        return tmp;
    }

    FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) {
        std::cerr << "[MOVE ASSIGN] this=" << this
              << " old=" << m_fd
              << " other=" << other.m_fd << '\n';

        if(this != &other) {
            if(this->m_fd != -1) {
                std::cerr << "  close(" << this->m_fd << ")\n";
                ::close(this->m_fd);
            }

            this->m_fd = other.m_fd;
            other.m_fd = -1;
        }

        std::cerr << "  result=" << m_fd << '\n';
        return *this;
    }

    FileDescriptor::FileDescriptor(FileDescriptor&& other) {
        std::cerr << "[MOVE CTOR ] this=" << this
              << " other=" << other.m_fd << '\n';
        *this = std::move(other);
    }

    FileDescriptor::~FileDescriptor() {
        std::cerr << "[DTOR      ] this=" << this
              << " fd=" << m_fd << '\n';

        if(this->m_fd != -1) {
            std::cerr << "  close(" << m_fd << ")\n";
            ::close(this->m_fd);
        }
    }
};