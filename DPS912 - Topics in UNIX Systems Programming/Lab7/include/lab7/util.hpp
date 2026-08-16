#ifndef L7_UTIL_HPP
#define L7_UITL_HPP

#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>

namespace L7 {
    std::vector<std::string> split(const std::string& completeCommand);

    // Assumes the strings used to create these will live and not die 
    // at-least they must live longer than the result from this vector
    std::vector<char*> createRawCommands(std::vector<std::string>& splitCommands);
    
    // Side effect: uses exec* so, lose control
    void runCommand(char* command);
};

#endif