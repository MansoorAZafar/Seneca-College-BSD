#ifndef AS2_FIFO_HPP
#define AS2_FIFO_HPP

#include "logger.hpp"
#include <string>
#include <vector>
#include <fcntl.h>
#include <stdexcept>
#include <string_view>
#include <arpa/inet.h>
#include <sys/stat.h>


namespace AS2 {
    class Fifo {
    private:
        int m_fd { -1 };

        bool write_full_message(const void* buf, size_t count); 
        bool read_full_message(void* buf, size_t count);
    public:
        int fd() const;

        Fifo() = default;
        Fifo(const char* fifoName, const int flag);

        Fifo(const Fifo&) = delete;
        Fifo& operator=(const Fifo&) = delete;
        Fifo(Fifo&& other);

        Fifo& operator=(Fifo&& other);

        bool write(const std::string_view& message);

        std::string read();

        void cleanup();

        ~Fifo();
    };
};

#endif