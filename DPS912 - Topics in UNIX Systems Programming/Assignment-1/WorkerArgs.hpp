#ifndef WORKER_ARGS_HPP
#define WORKER_ARGS_HPP
#include <array>
#include <string>

namespace AS1 {    

    constexpr const char* mbKey     { "--mb"     };
    constexpr const char* workerKey { "--worker" };
    constexpr const char* parentKey { "--parent" };
    constexpr const char* actionKey { "--action" };


    enum class WorkerAction {
        WORKER_CREATE,
        WORKER_READ
    };
    
    struct WorkerArgs {
        int mb;
        int worker;
        int parentPid;
        const char* executable;
        WorkerAction action;
    
        static WorkerArgs parse(int argc, char** argv);
        static std::array<std::string, 9> create(const WorkerArgs& args);
    };
};

#endif