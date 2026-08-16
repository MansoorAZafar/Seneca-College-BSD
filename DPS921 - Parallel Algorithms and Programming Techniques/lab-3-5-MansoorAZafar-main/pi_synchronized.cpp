#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <omp.h>

// report system time
void reportTime(const char* msg, std::chrono::steady_clock::duration span) {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(span);
    std::cout << msg << " took " <<
        ms.count() << " milliseconds" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << argv[0] << ": invalid number of arguments\n";
        std::cerr << "Usage: " << argv[0] << " no_of_slices\n";
        return 1;
    }

    const int n = std::atoi(argv[1]);
    const int nthreads { std::atoi(argv[2]) };
    std::chrono::steady_clock::time_point ts, te;

    // calculate pi by integrating the area under 1/(1 + x^2) in n steps
    ts = std::chrono::steady_clock::now();

    double pi, sum = 0.0;
    double stepSize = 1.0 / (double)n;

    #pragma omp parallel for reduction(+: sum) num_threads(nthreads)
    for (int i = 0; i < n; ++i) {
        const double x = ((double)i + 0.5) * stepSize;
        sum += 1.0 / (1.0 + x * x);
    }

    pi = 4.0 * sum * stepSize;

    te = std::chrono::steady_clock::now();

    std::cout << "n = " << n <<
        std::fixed << std::setprecision(15) <<
        "\npi(exact)   = " << 3.141592653589793 <<
        "\npi(calcd)   = " << pi << std::endl;

    reportTime("Integration", te - ts);
}
