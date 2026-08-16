#include "lab7/util.hpp"
namespace L7 {
    std::vector<std::string> split(const std::string& completeCommand) {
        std::vector<std::string> strings{};
        std::stringstream ss(completeCommand);
        std::string token;

        while(ss >> token) strings.push_back(token);

        return strings;
    }

    std::vector<char*> createRawCommands(std::vector<std::string>& splitCommands) {
        std::vector<char*> rawStrings;
        rawStrings.reserve(splitCommands.size() + 1);

        for(std::string& s : splitCommands) rawStrings.push_back(s.data());
        rawStrings.push_back(nullptr);

        return rawStrings;
    }

    void runCommand(char* command) {
        std::vector<std::string> splitCommands { L7::split(command) };
        std::vector<char*> rawCommands { L7::createRawCommands(splitCommands) };
        
        ::execvp(rawCommands[0], rawCommands.data());
    }
};