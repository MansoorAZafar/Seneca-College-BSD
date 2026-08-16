#ifndef L6_COMMAND_LINE_PARSER_HPP
#define L6_COMMAND_LINE_PARSER_HPP

#include <string>
#include <cctype>
#include <stdexcept>
#include <algorithm>
#include <string_view>
#include <unordered_map>


namespace L6 {
    using Args = std::unordered_map<std::string, std::string>;    
    
    const Args parse(int argc, char** argv);
};

#endif