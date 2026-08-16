#include "WorkerArgs.hpp"
#include <string_view>
#include <stdexcept>
#include <string>

AS1::WorkerArgs AS1::WorkerArgs::parse(int argc, char** argv) {
    WorkerArgs arguments{};
    arguments.executable = argv[0];

    for(int i = 1; i < argc; i += 2) {
        const std::string_view key { argv[i] };
        const int next { i + 1 };
        if(next > argc) {
            throw std::runtime_error("Missing value for argument: " + std::string(key));
        }

        const std::string_view value { argv[next] };
        if( key == mbKey ) {
            arguments.mb = std::stoi(argv[next]);
        } else if ( key == workerKey ) {
            arguments.worker = std::stoi(argv[next]);
        } else if ( key == parentKey ) {
            arguments.parentPid = std::stoi(argv[next]);
        } else if ( key == actionKey ) {
            arguments.action = static_cast<WorkerAction>(std::stoi(argv[next]));
        } else {
            throw std::runtime_error("Invalid Key or Argument. Format must be:\nexe-file --mb [int] --worker [int] --parent [int] --action [int] ");
        }
    }

    return arguments;
}

/**
 * Creates A string array ready for parsing for WorkerArgs::parse()
 *  - ensures each value is followed by a key
 *  - mimics args being passed like --[arg name] [value]
 *   i.e docker run --name app
 *      where key = name and value = app  
 * 
 * Format is:
 *  executable-name
 *  --mb
 *  mb
 *  --worker
 *  worker number
 *  --parentPid
 *  parent PID
 *  --action
 *  Create or read
 */
std::array<std::string, 9> AS1::WorkerArgs::create(const WorkerArgs& args) {
    const std::string sizeInMegabytesString { std::to_string(args.mb)                       };
    const std::string workerNumber          { std::to_string(args.worker)                   };
    const std::string parentPid             { std::to_string(args.parentPid)                };
    const std::string action                { std::to_string(static_cast<int>(args.action)) };

    return { 
        args.executable, 
        mbKey,
        sizeInMegabytesString,
        workerKey, 
        workerNumber,
        parentKey,  
        parentPid,
        actionKey,
        action
    };
}
