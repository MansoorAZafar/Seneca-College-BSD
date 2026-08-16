// Mansoor Zafar
#include <iostream> 
#include <cmath> 
#include <chrono> 

#include <vector> 
#include <thread> 
using namespace std::chrono;

class Version {
public:
    // used to identify the compiler used 
    // if you are not using a compiler listed replace blocks as appropiate 
    void operator()() const {
        std::cout << "Hello from the ";
#if defined(__GNUC__)           // for GCC  
        std::cout << "GNU compiler: ";   // Insert compiler name 
        std::cout << __GNUC__ << ":" << __GNUC_MINOR__ << " version\n"; // Insert version.revision.patch 

#elif defined(__INTEL_COMPILER)         // for Intel Parallel Studio 
        std::cout << "Intel compiler: ";   // Insert compiler name 
        std::cout << __INTEL_COMPILER << " version\n"; // Insert version.revision.patch 

#elif defined(_MSC_VER)         // for Visual Studio 
        std::cout << "Microsoft VC++: ";   // Insert compiler name 
        std::cout << _MSC_FULL_VER << " version\n"; // Insert version.revision.patch 

#else 
        std::cout << "??? compiler: ";   // None of the above 
#endif 
    }
};

// report system time 
// 
void reportTime(const char* msg, steady_clock::duration span) {
    auto ms = duration_cast<milliseconds>(span);
    std::cout << msg << " - took - " <<
        ms.count() << " milliseconds" << std::endl;
}

double magnitude(const double* x, size_t n, double& sum) {
    sum = 0.0;
    for (size_t i = 0; i < n; i++)
        sum += x[i] * x[i];
    return sqrt(sum);
}

void magnitudeParallel(const double* x, double& sum, size_t start, size_t end) {
    // Short Scalar Chaining instead of a long dependency chain
    /**
     * sum += x[i] * x[i]
     *  - introduces a "dependency chain"
     *      -> sum[1] depends on sum[0] to be done in this context
     *         as sum = sum + . . .
     *
     *  - We can instead fragment/split the accumulator
     *    into multiple independent ones
     *      - each independent one has its own chain but now we have
     *        n smaller chains rather than 1 long chain
     *
     *  - the CPU can run all fragmented instructions in parallel
     *    each iteration rather than the single iteration
     *      - ILP (Instruction Level Parallism )
     *
     *  - TLDR:
     *      - we are manually unrolling the loop
     *          - apparently compilers can just not unroll the loop
     *            if the length isn't known at compile time ... weird
     */
    double sum0 = 0.0, sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
    constexpr short fragments{ 4 };

    size_t i = start;
    const size_t numberOfElements = end - start;
    const size_t leftoverElements = numberOfElements % fragments;

    const size_t inRangeBoundary = end - leftoverElements;
    for (; i < inRangeBoundary; i += 4) {
        sum0 += x[i] * x[i];
        sum1 += x[i + 1] * x[i + 1];
        sum2 += x[i + 2] * x[i + 2];
        sum3 += x[i + 3] * x[i + 3];
    }

    // add any remaining items with a relatively short dependency chain
    while (i < end) {
        sum0 += x[i] * x[i];
        ++i;
    }

    sum = sum0 + sum1 + sum2 + sum3;
}

inline void insertToArray(double* arr, size_t startIndex, size_t endIndex) {
    for (size_t i = startIndex; i < endIndex; ++i) arr[i] = 1.0;
}

int main(int argc, char* argv[]) {
    Version version;
    version();
    if (argc != 3) {
        std::cerr << argv[0] << ": invalid number of arguments\n";
        std::cerr << "Usage: " << argv[0] << "  no_of_elements\n";
        return 1;
    }
    int n = std::atoi(argv[1]); // number of elements in a 
    const int numberOfThreads = std::atoi(argv[2]);
    steady_clock::time_point ts, te;

    // allocate memory 
    ts = steady_clock::now();
    double* a = new double[n];

    std::vector<std::thread> threads(numberOfThreads);
    const size_t partition = n / numberOfThreads;

 
    for (int i = 0; i < numberOfThreads; ++i) {
        const size_t start = (i * partition);
        const size_t end = i == numberOfThreads - 1 ? n : (start)+partition;

        threads[i] = std::thread(insertToArray, a, start, end);
    }


    te = steady_clock::now();
    reportTime(" - allocation and initialization", te - ts);

    for (std::thread& t : threads) {
        t.join();
    }
    // determine magnitude 
    ts = steady_clock::now();
    std::vector<double> magnitudes(numberOfThreads);

    for (int i = 0; i < numberOfThreads; i++) {
        const size_t start = (i * partition);
        const size_t end = i == numberOfThreads - 1 ? n : (start)+partition;

        threads[i] = std::thread(magnitudeParallel, a, std::ref(magnitudes[i]), start, end);
    }

    double length = 0.0;
    for (int i = 0; i < numberOfThreads; ++i) {
        threads[i].join();
        length += magnitudes[i];
    }

    length = sqrt(length);
    te = steady_clock::now();
    reportTime(" - magnitude calculation", te - ts);

    // display result 
    std::cout << "Magnitude of a[" << n << "] = " << length << std::endl;

    // deallocate host memory 
    delete[] a;
}
