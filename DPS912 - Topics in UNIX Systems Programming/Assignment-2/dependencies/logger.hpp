#ifndef MZ_LOGGER_HPP
#define MZ_LOGGER_HPP

#include <mutex>
#include <string>
#include <thread>
#include <fstream>
#include <iostream>
#include <string_view>
#include <condition_variable>


namespace mz {

    enum class LogLevel {
        DEBUG,
        WARN,
        INFO,
        TEST
    };

    inline const std::string to_string(const LogLevel& level);
    inline LogLevel from_string(const std::string_view& logLevelStr);


    namespace details {
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
                
                void push(const std::string& str) {
                    this->items[this->idx] = str;
                    this->idx = (this->idx + 1) % this->capacity;
                    
                    if(this->size != this->capacity) ++this->size;
                }
        
                std::string pop() {
                    if(this->empty()) return "";

                    const std::string item { this->items[this->head] };
                    this->head = (this->head + 1) % this->capacity;
                    
                    --this->size;
                    return item;
                }

                bool empty() const { return this->size == 0; }
                bool full() const { return this->size == this->capacity; }
            };

            std::thread writer {};
            Queue queue{};
            std::mutex mutex{};
            bool shutting_down { false };

            // a producer will wait for any free space
            std::condition_variable not_full;

            // a consumer will wait for it to be full
            std::condition_variable not_empty;

            LogLevel logLevel;
            std::string logfile {};
            std::ofstream ofstr{};
            void consumer() {
                while(true) {
                    std::unique_lock<std::mutex> lock(this->mutex);
                    // Wait until the queue is not empty or shutdown
                    this->not_empty.wait(lock, [&]() {
                        return this->shutting_down || !this->queue.empty();
                    });

                    if(this->shutting_down) break;
                
                    std::string message { this->queue.pop() };
                    lock.unlock();

                    this->not_full.notify_one();
                    if(!message.empty()) this->write(message);
                }
            }

            void producer(const std::string_view& message) {
                std::unique_lock<std::mutex> lock(this->mutex);
                // wait until the queue is not full or shutdown
                this->not_full.wait(lock, [&]() {
                    return this->shutting_down || !this->queue.full();
                });

                if(this->shutting_down) return;

                this->queue.push(std::string(message));
                lock.unlock();

                this->not_empty.notify_one();
            }

            void shutdown() {
                std::unique_lock<std::mutex> lock(this->mutex);
                this->shutting_down = true;
                lock.unlock();

                this->not_empty.notify_all();
                this->not_full.notify_all();
            }
            
            void write(const std::string& message) {
                this->ofstr << message << "\n";
                this->ofstr.flush();
            }

            Logger()
                : writer(std::thread(&Logger::consumer, this)), logLevel(LogLevel::INFO) {}
        public:
            static Logger& getInstance() {
                static Logger logger;
                return logger;
            }

            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;
            Logger(Logger&&) = delete;
            Logger& operator=(Logger&&) = delete;

            void logHeader() {
                const auto now = std::chrono::system_clock::now();  
                const std::time_t time { std::chrono::system_clock::to_time_t(now) };

                const char* timestr { std::ctime(&time) };
                const std::string message { 
                    "\n************************\n" 
                    + std::string(timestr) 
                    + "************************\n" 
                };
                
                this->log(LogLevel::INFO, message);
            }

            void setConfiguration(const LogLevel& level) { this->logLevel = level; }

            void setLogFile(const std::string_view& filename) {
                this->logfile = filename;
        
                if(this->ofstr.is_open()) this->ofstr.close();
                this->ofstr.open(this->logfile, std::ios::out | std::ios::app);
            }


            void log(const LogLevel& level, const std::string_view& message) {
                // Print ALL messages UNDER this level
                // Ex. DEBUG -> INFO
                // logLevel == DEBUG will print DEBUG and INFO
                // but Info has nothing under, so it 
                // just prints INFO logs
                if(this->logLevel > level) return;

                const std::string log_msg{ to_string(level) + " " + std::string(message) };
                this->producer(log_msg);
            }

            ~Logger() {
                this->shutdown();
                
                if(this->writer.joinable())this->writer.join();
                if(this->ofstr.is_open()) this->ofstr.close();
            }
        };
    };

    inline const std::string to_string(const LogLevel& level) {
        switch(level) {
            case LogLevel::DEBUG: return "[DEBUG]";
            case LogLevel::WARN:  return "[WARN]";
            case LogLevel::TEST:  return "[TEST]";
            default:              return "[INFO]";
        }
    }

    inline LogLevel from_string(const std::string_view& logLevelStr) {
        if(logLevelStr.compare("debug") == 0) {
            return LogLevel::DEBUG;
        } else if(logLevelStr.compare("warn") == 0) {
            return LogLevel::WARN;
        } else if(logLevelStr.compare("info") != 0) {
            std::cout << "Choosing LogLevel::INFO by default\n";  
        }

        return LogLevel::INFO;
    }

    inline void info(const std::string& msg)  { details::Logger::getInstance().log(LogLevel::INFO,  msg); }
    inline void warn(const std::string& msg)  { details::Logger::getInstance().log(LogLevel::WARN,  msg); }
    inline void debug(const std::string& msg) { details::Logger::getInstance().log(LogLevel::DEBUG, msg); }

    inline void setConfiguration(const LogLevel& level) { details::Logger::getInstance().setConfiguration(level); }
    inline void setLogFile(const std::string_view& filename) { details::Logger::getInstance().setLogFile(filename); }
    inline void logHeader() { details::Logger::getInstance().logHeader(); }
};

#endif