#ifndef L6_LOGGER_HPP
#define L6_LOGGER_HPP

#include <string>
#include <chrono>
#include <ctime>
#include <mutex>
#include <thread>
#include <iomanip>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <string_view>
#include <condition_variable>

namespace L6 {

    void l6_debug(const std::string& msg);
    void l6_warn(const std::string& msg);
    void l6_info(const std::string& msg);

    enum class LogLevel {
        DEBUG,
        WARN,
        INFO,
        TEST
    };

    LogLevel from_string(const std::string_view& logLevelStr);
    const std::string to_string(const LogLevel& level);

    class Logger {
    private:
        class Queue {
        private:
            static constexpr int capacity { 5 };    
            int size{0};
            int idx{0};
            int head{0};
            
            std::string items[capacity];
        public:
            Queue() = default;
            
            void push(const std::string& str);
            std::string pop();

            bool empty() const;
            bool full() const;
        };

        Queue queue{};

        std::mutex mutex{};
        
        // NOTE:
        // Originally used semaphores but switched since we can better 
        // control lifetimes and forcefully wake threads under a shutdown condition.
        // Semaphores are unaware during their wait but the wait for monitors 
        // (condition variables) allow us to choose a specific condition
        // std::counting_semaphore<5> slots {5};
        // std::counting_semaphore<5> items {0};

        // A flag to shut down any remaining producers / consumer(s)
        bool shutting_down { false };

        // a producer will wait for any free space
        std::condition_variable not_full;

        // a consumer will wait for it to be full
        std::condition_variable not_empty;

        LogLevel logLevel;
        std::string logfile {};
        std::ofstream ofstr{};
        
        std::thread writer;
        void consumer();
        void producer(const std::string_view& message);
        void shutdown();
        
        void write(const std::string& message);
        Logger();   
    public:
        static Logger& getInstance();

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;

        void logHeader();
        void setConfiguration(const LogLevel& level);
        void setLogFile(const std::string_view& filename);
        void log(const LogLevel& level, const std::string_view& message);

        ~Logger();
    };
};

#endif