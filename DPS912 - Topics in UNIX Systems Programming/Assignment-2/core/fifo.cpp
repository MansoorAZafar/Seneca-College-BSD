#include "fifo.hpp"
namespace AS2 {
    bool Fifo::write_full_message(const void* buf, size_t count) {
        const char* p { static_cast<const char*>(buf) };
        while(count > 0) {
            ssize_t bytes { ::write(this->m_fd, p, count) };
            if(bytes <= 0) {
                mz::warn("[Fifo] Write_full_message Error or Closed conn");
                return false;
            }

            p += bytes;
            count -= bytes;
        }

        return true;
    }

    bool Fifo::read_full_message(void* buf, size_t count) {
        char* p { static_cast<char*>(buf) };
        while(count > 0) {
            ssize_t bytes { ::read(this->m_fd, p, count) };
            if(bytes <= 0) {
                mz::warn("[Fifo] Read_full_message Error or Closed conn");
                return false;
            }

            p += bytes;
            count -= bytes;
        }

        return true;
    }

    int Fifo::fd() const { return this->m_fd; }


    Fifo::Fifo(const char* fifoName, const int flag) {
        ::mkfifo(fifoName, 0666);
        this->m_fd = ::open(fifoName, flag);

        if(this->m_fd == -1) {
            mz::warn("[Fifo] ::open() failed");
            throw std::runtime_error("open()");
        }
    }

    Fifo::Fifo(Fifo&& other) {
        *this = std::move(other);
    }

    Fifo& Fifo::operator=(Fifo&& other) {
        if(this != &other) {
            if(this->m_fd != -1) ::close(this->m_fd);
            this->m_fd = other.m_fd;
            other.m_fd = -1;
        }

        return *this;
    }

    bool Fifo::write(const std::string_view& message) {
        const uint32_t length { ::htonl(static_cast<uint32_t>(message.size())) };
        if(!this->write_full_message(&length, sizeof(length))) {
            mz::warn("[Fifo]: Failed to write length prefix");
            return false;
        };    

        return this->write_full_message(message.data(), message.size());
    }

    std::string Fifo::read() {
        uint32_t length { 0 };
        if(!this->read_full_message(&length, sizeof(length))) {
            mz::warn("[Fifo]: Failed to read length prefix");
            return "";
        }

        uint32_t message_length = ::ntohl(length);
        std::vector<char> buffer(message_length);

        if(!this->read_full_message(buffer.data(), message_length)) {
            mz::warn("[Fifo]: Failed to read full message");
            return "";
        }

        return std::string(buffer.begin(), buffer.end());
    }

    void Fifo::cleanup() {
        if(this->m_fd != -1) ::close(this->m_fd);
    }

    Fifo::~Fifo() {
        mz::debug("[Fifo] closing fd: " + std::to_string(this->m_fd));
        this->cleanup();
    }

};