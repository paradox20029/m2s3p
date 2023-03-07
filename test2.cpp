#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>
#include <string>
using namespace std;
#define NUM_THREADS 8
#define MAX 1000000
int data[MAX];
long global_sum = 0;
/*includes the necessary header files, defines some constants and global variables. 
NUM_THREADS defines the number of threads to use, MAX defines the size of the data array, 
and global_sum is the variable that will store the final sum.*/
//-------------------
/* main function of the program. omp_get_num_procs() returns the number of available 
processing cores on the machine. The srand function initializes the random number generator with the current time. 
The loop initializes each element of the data array with a random integer between 0 and 19.*/

int main(int argc, char *argv[])
{
    int cores = omp_get_num_procs();
    cout << "The number of cores on this machine = " << cores << endl;
    srand(time(NULL));
    for (int i = 0; i < MAX; i++)
    {
        data[i] = rand() % 20;
    }
    /* parallel section of the code. The pragma directive instructs the compiler to parallelize the code that follows it. 
    The num_threads clause specifies the number of threads to use for the parallel region. The default(none) clause forces the
     programmer to explicitly specify which variables are shared and which are private. The shared clause specifies that the 
     data and global_sum variables are shared among all threads.Inside the parallel region, each thread computes a local sum 
     of a portion of the data array. The omp_get_thread_num() function returns the ID of the current thread. The range variable 
     calculates the number of elements in the data array that each thread is responsible for. The start and end variables define 
     the range of indices that each thread will sum over.After each thread has computed its local sum, the critical directive is 
     used to ensure that only one thread at a time can update the global_sum variable. This is necessary to avoid race conditions and ensure that the final result is correct*/
#pragma omp parallel num_threads(NUM_THREADS) default(none) shared(data,global_sum)
{
    long tid = omp_get_thread_num();
    long sum = 0;
    int range = MAX / NUM_THREADS;
    int start = tid * range;
    int end = start + range;
    for (int i = start; i < end; i++)
    {
        sum += data[i];
    }
#pragma omp critical
    {
        global_sum += sum;
    }
}
cout << "The final sum = " << global_sum << endl;
return 0;
}