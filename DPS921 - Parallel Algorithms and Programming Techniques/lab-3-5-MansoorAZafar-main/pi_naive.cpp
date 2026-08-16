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
        std::cerr << "Usage: " << argv[0] << " no_of_slices, no_of_threads\n";
        return 1;
    }

    const int n = std::atoi(argv[1]);
    const int nthreads { std::atoi(argv[2]) };
    std::chrono::steady_clock::time_point ts, te;

    // calculate pi by integrating the area under 1/(1 + x^2) in n steps
    ts = std::chrono::steady_clock::now();

    double x, pi, sum = 0.0;
    double stepSize = 1.0 / (double)n;

    // Cache lines are generally 64 bytes,
    // we are dealing with doubles
    // 64 / 8 --> 8
    // [number_of_threads][8]
    // each thread gets a padding of 7 elements (first one is for it to use)
    double* arr = new double[nthreads] ();

    #pragma omp parallel for num_threads(nthreads)
    for(int i = 0; i < n; ++i) {
        const int threadID { omp_get_thread_num() };
        const double x { (static_cast<double>(i) + 0.5) * stepSize };

        arr[threadID] += 1.0 / (1.0 + x * x);
    }

    for(int i = 0; i < nthreads; ++i) sum += arr[i];
    pi = 4.0 * sum * stepSize;
    
    delete[] arr;
    te = std::chrono::steady_clock::now();

    std::cout << "n = " << n <<
        std::fixed << std::setprecision(15) <<
        "\npi(exact)   = " << 3.141592653589793 <<
        "\npi(calcd)   = " << pi << std::endl;

    reportTime("Integration", te - ts);
}