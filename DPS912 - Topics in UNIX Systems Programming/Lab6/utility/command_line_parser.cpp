#include "utility/command_line_parser.hpp"
#include <iostream>

namespace L6 {
    const Args parse(int argc, char **argv) {
        constexpr const char delim { '-' };
        Args cla{};

        const auto to_lower = [](std::string& str) -> void {
            std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { 
                return std::tolower(c); 
            });
        };

        for(int i = 1; i < argc; i += 2) {
            std::string_view word { argv[i] };
            
            if(word.front() == delim && (i + 1) < argc) {
                word.remove_prefix(1);
                std::string key{word};
                std::string value{argv[i + 1]};

                
                to_lower(key);
                to_lower(value);
                
                cla[key] = value;
            } else {
                throw std::runtime_error("Failed to (some) CLI Args. Have all args delimited by -[key] [value].\nEx: ./file.exe -v 2");
            }
        }

        return cla;
    }
};