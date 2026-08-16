// Discretize the Elements of an Array
// Chris Szalwinski
// 2020/11/27


#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "mpi.h"
#define TIME 1
/*
 Code Explanation
 The master process

    -allocates memory for the array of size specified on the command line
    -initializes the elements of the array to random values
    -scatters the data elements to each process including itself
    -converts its part of the data
    -gathers the converted data from all other processes
    -determines the number of elements of value less than 0.707 for all processes, including itself
    -accumulates the times for each process
    -determines the total time spent by all processes
    -determines the wall clock time for all processes running concurrently

Each worker process

    -allocates memory for its part of the data
    -receives its part of the data from the master process
    -converts its part of the data
    -returns the converted data to the master process
    -returns the conversion time to the master process
*/

// report processor time
//
void reportTime(const char* msg, int i, double span) {
    printf("Process %d: %-12s took %7.4lf seconds\n", i, msg, span);
}

// discretize data[n] into 0s and 1s
//
void discretize(float* data, int n) {
    for (int i = 0; i < n; i++)
        data[i] = (pow(sin(data[i]), cos(data[i])) +
            pow(cos(data[i]), sin(data[i]))) / 2.0f;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "%s : invalid number of arguments\n"
            "Usage: %s no_of_elements\n", argv[0], argv[0]);
        return 1;
    }

    // retrieve number of elements
    int n = atoi(argv[1]);
    int rank, np;
    
    //
    // initialize MPI
    //
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int nPerProcess = n / np;
    n = nPerProcess * np;

    int zeroes = 0;
    float* data = NULL;
    float* result = NULL;

    // get MPI wall clock time start
    float begin, end;
    begin = MPI_Wtime();

    if (rank == 0) {
        // initialization

        // get MPI allocation time start
        float sTime = MPI_Wtime();

        data = (float*)malloc(n * sizeof(float));
        result = (float*)malloc(n * sizeof(float));
        
        // set original data
        for (int i = 0; i < n; i++)
            data[i] = (float)rand() / RAND_MAX;

        // get MPI allocation time end
        float eTime = MPI_Wtime();
        reportTime("Allocation", 0, );

        // conversion

        // get MPI time start
        sTime = MPI_Wtime();

        // scatter original data to all workers including master
        MPI_Scatter(data, nPerProcess, MPI_FLOAT, result, nPerProcess, MPI_FLOAT, 0, MPI_COMM_WORLD);
        discretize(data, nPerProcess);

        // gather converted data from all workers
        MPI_Gather(data, nPerProcess, MPI_FLOAT, result, nPerProcess, MPI_FLOAT, 0, MPI_COMM_WORLD);

        // get MPI time end
        eTime = MPI_Wtime();

        // identify 0s and 1s
        for (int i = 0; i < nPerProcess; i++)
            if (data[i] < 0.707f)
                zeroes++;
        for (int i = nPerProcess; i < n; i++)
            if (result[i] < 0.707f)
                zeroes++;

        // report timing statistics

        // error handler declaration
        MPI_Status status;
        double totalTime = 0, time = 0.0;

        double totalTime = 0, time = 0.0;
        reportTime("Conversion", 0, );
        for (int i = 1; i < np; i++) {

            // collect time for process i
            MPI_Recv(&time, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if(status.MPI_ERROR) {
                printf("[DEBUG ERROR]: %d\n", status.MPI_SOURCE);
            }

            reportTime("Conversion", i, time);
            totalTime += time;
        }

        reportTime("Sum of All", 0, totalTime);
    }
    else {
        // worker process
        float* data = (float*)malloc(nPerProcess * sizeof(float));

        // get MPI time
        float sTime = MPI_Wtime();

        // scatter receiver of original data
        MPI_Scatter(data, nPerProcess, MPI_FLOAT, data, nPerProcess, MPI_FLOAT, 0, MPI_COMM_WORLD);
        discretize(data, nPerProcess);

        // gather converted data and send to master
        MPI_Gather(data, nPerProcess, MPI_FLOAT, result, nPerProcess, MPI_FLOAT, 0, MPI_COMM_WORLD);

        // get MPI time
        float eTime = MPI_Wtime();
        free(data);

        // report time
        reportTime("Worker Time: ", rank, eTime - sTime);

        // send time to master
        const double time = eTime - sTime;
        MPI_Send(&time, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
    }

    // get MPI wall clock time end
    end = MPI_Wtime();

    if (rank == 0) {
        reportTime("Conversion Time - Wall clock", 0, end - begin);

        // get MPI deallocation time start
        begin = MPI_Wtime();

        free(data);
        free(result);

        // get MPI deallocation time end
        end = MPI_Wtime();

        reportTime("Deallocation", 0, end - begin);
        printf("Result: %d = %d (0s) + %d (1s)\n", n, zeroes, n - zeroes);
    }

    // close MPI
    MPI_Finalize();

    return 0;
}
