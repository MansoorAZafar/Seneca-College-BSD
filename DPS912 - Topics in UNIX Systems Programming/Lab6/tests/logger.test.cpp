#include <string>
#include <thread>
#include <vector>
#include <iostream>
#include "utility/logger.hpp"

using namespace L6;
int main() {
    Logger& logger { Logger::getInstance() };
        
    logger.setLogFile("test.log");
    logger.setConfiguration(LogLevel::DEBUG);

    constexpr int num_threads {10};
    std::vector<std::thread> threads(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread([=]() {
            const size_t id = std::hash<std::thread::id>{}(std::this_thread::get_id());

            for (int j = 0; j < 3; ++j) {
                l6_debug("Thread " + std::to_string(id) +
                        " message " + std::to_string(j));
            }
        });
    }

    for(std::thread& thread : threads) thread.join();
    return 0;
}