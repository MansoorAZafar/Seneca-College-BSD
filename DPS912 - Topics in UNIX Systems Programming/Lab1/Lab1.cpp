#include <string_view>
#include <algorithm>
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cctype>
#include <string>

#define PROCESS_PATH "/proc"
#define STATUS_PATH  "/status"

struct Process {
    int pid{0}, vmRSS{0}, vmSize{0};
    char state {'\0'};
    std::string name{}, umask{};

    inline bool isComplete() const {
        return this->pid && this->vmRSS && this->vmSize && !this->state == '\0' && !name.empty();
    }

    void printBasic() const;
    friend std::ostream& operator<<(std::ostream& ostr, const Process& process);
};

void Process::printBasic() const {
       std::cout << "[Name]: " << this->name << "\n\t"
                << std::setw(15) << "[Process ID]: " << std::setw(10) << this->pid << "\n\t"
                << std::setw(15) << "[VmSize]: " << std::setw(10)
                        << this->vmSize << " kB \t(Total memory used (Virtual))\n\t"
                << std::setw(15) << "[VmRSS]: " << std::setw(10)
                        << this->vmRSS << " kB \t(Actual RAM used)\n\n";
}

std::ostream& operator<<(std::ostream& ostr, const Process& process) {
    return ostr << "[Name]: " << process.name << "\n\t"
                << std::setw(15) << "[Process ID]: " << process.pid << "\n\t"
                << std::setw(15) << "[State]: " << process.state
                    << (process.state == 'R' ? " [running]" : " [sleeping]") << "\n\t"
                << std::setw(15) << "[VmSize]: " << process.vmSize << "\n\t"
                << std::setw(15) << "[VmRSS]: " << process.vmRSS << "\n\n";
}

inline bool validProcess(const char* process) {
    return process != nullptr && std::isdigit(process[0]);
}

Process getProcessDetails(const char* pid) {
    constexpr const char* PID_DELIMITER    = "Pid";
    constexpr const char* STATE_DELIMITER  = "State";
    constexpr const char* VMRSS_DELIMITER  = "VmRSS";
    constexpr const char* VMSIZE_DELIMITER = "VmSize";
    constexpr const char* NAME_DELIMITER   = "Name";
    constexpr const char* UMASK_DELIMITER  = "Umask";

    const std::string path = std::string(PROCESS_PATH) + "/" + pid + STATUS_PATH;
    std::ifstream ifstr{path};
    if(!ifstr) return {};

    std::string line;
    Process content{};
    while(std::getline(ifstr, line)) {
        if(content.isComplete()) break;

        const size_t colon = line.find(":");
        const std::string_view key = std::string_view(line).substr(0, colon);
        const std::string value = line.substr(colon + 1);

        std::istringstream iss(value);
        if(key == PID_DELIMITER) {
            iss >> content.pid;
        } else if (key == STATE_DELIMITER) {
            iss >> content.state;
        } else if (key == VMRSS_DELIMITER) {
            iss >> content.vmRSS;
        } else if (key == VMSIZE_DELIMITER) {
            iss >> content.vmSize;
        } else if (key == NAME_DELIMITER) {
            iss >> content.name;
        } else if (key == UMASK_DELIMITER) {
            iss >> content.umask;
        }
    }

    std::cout << content;
    return content;
}

int main() {
    /**
     * Vector vs PriorityQueue
     * Vector:
     *  - Vector O(1) emplace_back O(1) amoritzed happens N times
     *  - nth_element -> O(n)
     *  - sort only 0-k -> O(klogk)
     *      = O(n + klogk) average
     *
     * PriorityQueue:
     *  - emplace -> O(logk) happens N times
     *  - popping for printing -> O(logk) happens K times
     *      = O(nlogk + klogk) -> O(n log k) (remove klogk since its small)
     *
     * On average vector beats priorityqueue
     */
    std::vector<Process> processes{};
    auto comparator = [](Process& left, Process& right) -> bool { return left.vmRSS > right.vmRSS; };

    DIR* directoryStream = opendir(PROCESS_PATH);
    if(directoryStream == NULL) {
        std::cerr << "[ERROR] Failed to open path: " << PROCESS_PATH << "\n";
        exit(1);
    }

    dirent* entity{};
    std::cout << "\033[32m--- Listing ALL Pid, State, VmSize VmRSS"
            << " of all accessible processes in /proc/[pid]/status ---\033[0m \n";
    while((entity = readdir(directoryStream)) != NULL) {
        if(!validProcess(entity->d_name)) continue;
        processes.emplace_back(getProcessDetails(entity->d_name));
    }

    closedir(directoryStream);
    constexpr int topK = 5;

    // O(n) operation on avg
    std::nth_element(
        processes.begin(),
        processes.begin() + topK,
        processes.end(),
        comparator
    );

    // O(k log k)
    std::sort(processes.begin(), processes.begin() + topK, comparator);
    std::cout << "\033[32m--- Listing top " << topK << " processes ---\033[0m\n";
    for(int i = 0; i < topK; ++i) {
        processes[i].printBasic();
    }

    return 0;
}