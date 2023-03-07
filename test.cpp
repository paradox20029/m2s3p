#include <iostream> //several libraries, including iostream, omp.h, and time.h.
#include <stdlib.h> //provides functions for memory allocation, random number generation, and other basic operations.
#include <omp.h>    //provides the OpenMP API for parallel programming.
#include <time.h>   //provides functions for measuring time.
#include <string>   //provides string operations.

using namespace std;
// NUM_THREADS is the number of threads to be used for parallelization.
// MAX is the size of the data array.
// data is an array of integers that will be summed.
// global_sum is a long integer that will hold the final sum of the data array.

#define NUM_THREADS 8
#define MAX 1000000

int data[MAX];
long global_sum = 0;

int main(int argc, char *argv[])
{
    // omp_get_num_procs() returns the number of processors on the machine.
    // cout prints a message to the console.
    int cores = omp_get_num_procs();
    cout << "The number of cores on this machine = " << cores << endl;
    // srand(time(NULL)) seeds the random number generator with the current time.

    srand(time(NULL));

    // data array with random integers between 0 and 19 using rand() % 20
    for (int i = 0; i < MAX; i++)
    {
        data[i] = rand() % 20;
    }
    // #pragma omp parallel starts a parallel region, which will execute in parallel on multiple threads.
    // num_threads(NUM_THREADS) specifies the number of threads to use for the parallel region.
    // shared(global_sum) declares global_sum as a shared variable that can be accessed by all threads.
    // Inside the parallel region, local_sum is a variable that will hold the sum of the data array for each thread.
    // #pragma omp for indicates that the following loop should be executed in parallel by all threads.
    // The for loop iterates over each element in the data array and adds it to the local_sum variable for that thread.
    // #pragma omp critical creates a critical section, which ensures that only one thread can access global_sum at a time. Inside the critical section, each thread adds its local_sum to the global_sum.
    //  Compute the sum of the data array in parallel
#pragma omp parallel num_threads(NUM_THREADS) shared(global_sum)
    {
        long local_sum = 0;

#pragma omp for
        for (int i = 0; i < MAX; i++)
        {
            local_sum += data[i];
        }

#pragma omp critical
        {
            global_sum += local_sum;
        }
    }

    cout << " final sum is = " << global_sum << endl;

    return 0;
}