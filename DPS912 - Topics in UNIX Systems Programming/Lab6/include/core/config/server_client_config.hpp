#ifndef L6_SERVER_HELPER_HPP
#define L6_SERVER_HELPER_HPP

#include <string>
#include <string_view>
#include "utility/command_line_parser.hpp"

namespace L6 {
    enum class ServerArgs {
        DOMAIN,
        LOG_LEVEL
    };

    const std::string to_string(ServerArgs arg);
    Args init(int argc, char** argv);
};
#endif