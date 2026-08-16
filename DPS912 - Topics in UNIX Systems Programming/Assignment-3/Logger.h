#ifndef ASSIGNMENT_3_LOGGER_H
#define ASSIGNMENT_3_LOGGER_H

#include "Commons.hpp"
#include <thread>
#include <chrono>
#include <string>
#include <utility>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <string_view>
#include <system_error>
#include <netinet/in.h>
#include <sys/socket.h>

enum LogLevel {
    DEBUG,
    WARNING,
    ERROR,
    CRITICAL
};

int InitializeLog();
void SetLogLevel(const LogLevel&);

void Log(const LogLevel&, const char*, const char*, const int, const std::string_view&);
void ExitLog();

void* recv(void* args);

namespace AS3 {
    const char* const to_string(const LogLevel&);
    LogLevel FromLogLevelString(const std::string_view& level);    

    extern bool is_running;     
    extern int fd;

    extern pthread_t thread_id;
    extern sockaddr_in address;
    extern socklen_t   length;
    
    extern Mutex mutex;
    extern LogLevel filter_level;
};

#endif