#include "core/config/server_client_config.hpp"
#include <iostream> 

namespace L6 {    
    const std::string to_string(ServerArgs arg) {
        switch(arg) {
            case ServerArgs::DOMAIN: return "domain";
            case ServerArgs::LOG_LEVEL: return "log-level";
            default: return "Unknown";
        }
    }

    Args init(int argc, char **argv) {
        const std::string DEFAULT_DOMAIN    { "stream" }; 
        const std::string DEFAULT_LOG_LEVEL { "info"   }; 

        Args args = parse(argc, argv);
        const auto assignDefaultArgumentsIfNeeded = [&args](const std::string& key, const std::string& val) {
            if(args.find(key) == args.end()) {
                args[key] = val;
            }
        };

        assignDefaultArgumentsIfNeeded(to_string(ServerArgs::DOMAIN), DEFAULT_DOMAIN);
        assignDefaultArgumentsIfNeeded(to_string(ServerArgs::LOG_LEVEL), DEFAULT_LOG_LEVEL);

        return args;
    };
}
