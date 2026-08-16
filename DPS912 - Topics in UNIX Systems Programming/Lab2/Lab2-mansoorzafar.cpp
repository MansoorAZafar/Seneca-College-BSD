#include <vector>
#include <string>
#include <utility>
#include <iomanip>
#include "pidUtil.h"

/**
 * Pass in any function and we pass in the arguments
 *  - Since all funcs return the same thing of ErrStatus
 *      we can just use a generic pass to handle
 *      any of the functions
 *  - We forward the reference (T&&) since we want
 *    to retain the original value category (lvalue, rvalue ...)
 * 
 *  - We use std::forward since we want to pass the 
 *    original quantifier into the actual function
 *      - otherwise it'll always be a lvalue ref
 */
template <class Func, class... Args>
bool safeExecute(Func&& func, Args&&... args) {
    if (ErrStatus status = func(std::forward<Args>(args)...); status != Err_OK) {
        std::cout << GetErrorMsg(status) << "\n";    
        return false;
    }
    return true;
}

int main() {
    std::vector<int> pids{};
    safeExecute(GetAllPids, pids);    

    int pid{ 1 };
    std::string pidName{};
    if(safeExecute(GetNameByPid, pid, pidName)) std::cout << "[PID 1 Name]: " << pidName << "\n";

    pidName = "Lab2";
    if(safeExecute(GetPidByName, pidName, pid)) std::cout << "[" << pidName << " PID]: " << pid << "\n";

    pidName = "Lab11";
    if(safeExecute(GetPidByName, pidName, pid)) std::cout << "[" << pidName << " PID]: " << pid << "\n";
}
