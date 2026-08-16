#include <string>
#include <vector>
#include <numeric>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using str = std::string;
int main(int argc, char** argv) {
    const std::vector<str> cmds(argv + 1, argv + argc);
    const str cmd{ std::accumulate(std::next(cmds.begin()), cmds.end(), cmds[0], [](const str& a, const str& b) {return a + " | " + b;}) };
    
    ::system(cmd.c_str());
    return 0;
}