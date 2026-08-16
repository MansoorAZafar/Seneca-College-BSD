#include "utility/logger.hpp"
namespace L6 {

    void l6_debug(const std::string& msg) {
        Logger::getInstance().log(LogLevel::DEBUG, msg);        
    }
    
    void l6_warn(const std::string& msg) {
        Logger::getInstance().log(LogLevel::WARN, msg);        
    }

    void l6_info(const std::string& msg) {
        Logger::getInstance().log(LogLevel::INFO, msg);        
    }

    LogLevel from_string(const std::string_view& logLevelStr) {
        if(logLevelStr.compare("debug") == 0) {
            return LogLevel::DEBUG;
        } else if(logLevelStr.compare("warn") == 0) {
            return LogLevel::WARN;
        } else if(logLevelStr.compare("info") != 0) {
            std::cout << "Choosing LogLevel::INFO by default\n";  
        }

        return LogLevel::INFO;
    }

    const std::string to_string(const LogLevel& level) {
        switch(level) {
            case LogLevel::DEBUG: return "[DEBUG]";
            case LogLevel::WARN:  return "[WARN]";
            case LogLevel::TEST:  return "[TEST]";
            default:              return "[INFO]";
        }
    }

    std::string Logger::Queue::pop() {
        if(this->empty()) return "";

        const std::string item { this->items[this->head] };
        this->head = (this->head + 1) % this->capacity;
        
        --this->size;
        return item;
    }

    void Logger::Queue::push(const std::string& str) {
        this->items[this->idx] = str;
        this->idx = (this->idx + 1) % this->capacity;
        
        if(this->size != this->capacity) ++this->size;
    }

    bool Logger::Queue::empty() const {
        return this->size == 0;
    }

    bool Logger::Queue::full() const {
        return this->size == this->capacity;
    }

    void Logger::consumer() {
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

    void Logger::producer(const std::string_view& message) {
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

    void Logger::write(const std::string& message) {
        this->ofstr << message << "\n";
        this->ofstr.flush(); // Write to file no matter what
    }

    Logger::Logger() {
        this->writer = std::thread(&Logger::consumer, this);
    }

    Logger& Logger::getInstance() {
        static Logger logger;
        return logger;
    }
    
    void Logger::logHeader() {
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

    void Logger::setConfiguration(const LogLevel& level) {
        this->logLevel = level;
    }

    void Logger::setLogFile(const std::string_view& filename) {
        this->logfile = filename;
        
        if(this->ofstr.is_open()) this->ofstr.close();
        this->ofstr.open(this->logfile, std::ios::out | std::ios::app);
    }

    void Logger::log(const LogLevel& level, const std::string_view& message) {
        // Print ALL messages UNDER this level
        // Ex. DEBUG -> INFO
        // logLevel == DEBUG will print DEBUG and INFO
        // but Info has nothing under, so it 
        // just prints INFO logs
        if(this->logLevel > level) return;

        const std::string log_msg{ to_string(level) + " " + std::string(message) };
        this->producer(log_msg);
    }

    void Logger::shutdown() {
        std::unique_lock<std::mutex> lock(this->mutex);
        
        this->shutting_down = true;
        
        lock.unlock();

        this->not_empty.notify_all();
        this->not_full.notify_all();
    }

    Logger::~Logger() {
        this->shutdown();

        if(this->writer.joinable())this->writer.join();
        if(this->ofstr.is_open()) this->ofstr.close();
    }
};