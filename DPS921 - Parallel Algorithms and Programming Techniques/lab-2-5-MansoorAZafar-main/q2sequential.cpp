// provide your serial matrix multiplication here
#include <iostream> 
#include <chrono>

using namespace std::chrono;
void reportTime(const char *msg, steady_clock::duration span) {

    auto ms = duration_cast<milliseconds>(span);
    std::cout << msg << " - took - " <<
        ms.count() << " millisecs" << std::endl;
}

int main(int argc, char** argv) { 
    if (argc != 2) { 
        std::cerr << argv[0] << ": invalid number of arguments\n"; 
        std::cerr << "Usage: " << argv[0] << "  size_of_vector\n"; 
        return 1; 
    } 

    int n = std::atoi(argv[1]); 
    steady_clock::time_point ts, te;

    ts = steady_clock::now();
    float* h_a = new float[n * n]; 
    float* h_b = new float[n * n]; 
    float* h_c = new float[n * n]; 

    for (int i = 0, kk = 0; i < n; i++) 
        for (int j = 0; j < n; j++, kk++) 
            h_a[kk] = h_b[kk] = (float)kk / (n * n); 
 
    te = steady_clock::now();
    reportTime("allocation and initialization", te - ts);

    ts = steady_clock::now();
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) { 
            float sum = 0.0f; 
            for (int k = 0; k < n; k++) sum += h_a[i * n + k] * h_b[k * n + j]; 
            h_c[i * n + j] = sum; 
        } 
        
    te = steady_clock::now();
    reportTime("matrix-matrix multiplication", te - ts);
    std::cout << "done" << std::endl; 
 
    delete[] h_a; 
    delete[] h_b; 
    delete[] h_c; 
}