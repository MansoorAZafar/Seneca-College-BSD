#include "Logger.h"

namespace AS3 {
    bool is_running { true };     
    int fd { -1 };

    pthread_t thread_id {};
    sockaddr_in address {};
    socklen_t   length  {};

    Mutex mutex {};
    LogLevel filter_level { DEBUG };
};

const char* const AS3::to_string(const LogLevel& level) {
    switch(level) {
        case CRITICAL: return "critical";
        case ERROR: return "error";
        case WARNING: return "warning";
        
        default: return "debug";
    }
}

LogLevel AS3::FromLogLevelString(const std::string_view& level) {
    if (level == "critical") return LogLevel::CRITICAL;
    else if (level == "error") return LogLevel::ERROR;
    else if (level == "warning") return LogLevel::WARNING;
    return LogLevel::DEBUG;
}

void* recv(void* arg) {
    constexpr int BUF_LEN { 4096 };
    const int fd { *(static_cast<int*>(arg)) };

    char buffer[BUF_LEN] {};
    constexpr char delimiter_start { '<' };
    constexpr char delimiter_end   { '>' };

    // Parses anything in < > and returns the next position to start
    const auto parse_delim = [&delimiter_start, &delimiter_end](
        const std::string_view& message, 
        const size_t& begin = 0
    ) -> std::pair<std::string, size_t> {
        const size_t start { message.find_first_of(delimiter_start, begin) };
        const size_t end   { message.find_first_of(delimiter_end  , begin) };

        if(start == std::string::npos || end == std::string::npos) {
            // Nothing to parse
            return std::pair<std::string, size_t>("", -1);
        }

        return std::pair<std::string, size_t>(message.substr(start + 1, end - start - 1), end + 1);
    };

    while(AS3::is_running) {
        const ssize_t len { ::recvfrom(fd, buffer, BUF_LEN - 1, 0, nullptr, nullptr) };

        if(len > 0) {
            buffer[len] = '\0';
            // std::cout << "received: " << buffer << "\n";

            try {
                const std::string_view message { buffer };
                const auto [parsed, _] { parse_delim(message) };                
                // std::cout << "Parsed: " << parsed << "\n";
                if(parsed == "") throw std::runtime_error("nothing to parse");

                const LogLevel level { AS3::FromLogLevelString(parsed) };
                // std::cout << "level: " << AS3::to_string(level) << "\n";

                AS3::mutex.lock();
                AS3::filter_level = level;
                AS3::mutex.unlock();

            } catch (const std::exception& e) { std::cerr << e.what() << "\n"; }

        } else if(len == 0) { AS3::is_running = false; }
        else {
            if(errno == EAGAIN || errno == EWOULDBLOCK) { continue; }
            else if (errno == EINTR) { AS3::is_running = false; }
        
            std::cerr << "[Logger]: read failed: " << std::strerror(errno) << "\n";
            AS3::is_running = false;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ::pthread_exit(NULL);
}

int InitializeLog() {
    AS3:: fd = { ::socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0) };
    if(AS3::fd == -1) throw std::system_error(errno, std::system_category(), "socket");

    AS3::address = { AF_INET, ::htons(AS3::SERVER_PORT) };
    AS3::length  = { sizeof(AS3::address) };

    // ::pthread_mutex_init(&AS3::lock, nullptr);
    AS3::mutex.init();
    
    const int result { ::pthread_create(&AS3::thread_id, nullptr, recv, &AS3::fd) };
    if(result != 0) throw std::system_error(errno, std::system_category(), "pthread_create");

    return AS3::fd;
}

void Log(
    const LogLevel& level, 
    const char* program, 
    const char* function, 
    const int line, 
    const std::string_view& message
) {
    AS3::mutex.lock();
    // std::cout << "Comparing level: " << AS3::to_string(level) << " to filter_level: " << AS3::to_string(AS3::filter_level) << "\n";
    if(level < AS3::filter_level) {
        // THROW AWAY 
        // Ex.
        // level = DEBUG (0) && filter_level = CRITICAL (3)
        // On CRITICAL, we only show CRITICAL+ --> So we discard
        // But if level = CRITICAL (3) && filter_level = DEBUG (0)
        // we keep, since debug shows ALL --> 3 < 0 ? FALSE
        AS3::mutex.unlock();
        return;
    }

    const std::string logLevelString { AS3::to_string(level) };
    AS3::mutex.unlock();

    const auto now = std::chrono::system_clock::now();  
    const std::time_t time { std::chrono::system_clock::to_time_t(now) };

    std::string timestr { std::ctime(&time) };
    timestr.pop_back();

    //Message Format:
    // [LEVEL - TIME]: MESSAGE
    //      {filename}: {line_number} - {function_name}
    // EX.
    // [DEBUG - 10:25:30]: File descriptor returned 23
    //      Logger.cpp: 14 - InitializeLog()
    std::ostringstream string_stream {};
    string_stream << "[ " << logLevelString << " - " << timestr << "]: "
        << message << "\n" 
        << program << ": " << line << " - " << function << "\n";

    const std::string msg { string_stream.str() };    
    if(::sendto(
        AS3::fd, 
        msg.data(), 
        msg.size(), 
        0, 
        reinterpret_cast<sockaddr*>(&AS3::address), 
        AS3::length
    ) == -1) throw std::system_error(errno, std::system_category(), "sendto");
}

void SetLogLevel(const LogLevel& level) { 
    AS3::mutex.lock();
    AS3::filter_level = level;
    AS3::mutex.unlock(); 
}

void ExitLog() {    
    AS3::is_running = false;

    AS3::mutex.cleanup();
    // If it's during a read, shut it down regardless
    // cancel all reads or writes and make it return
    ::shutdown(AS3::fd, SHUT_RDWR);
    ::pthread_join(AS3::thread_id, nullptr);

    if(AS3::fd != -1) ::close(AS3::fd);
}