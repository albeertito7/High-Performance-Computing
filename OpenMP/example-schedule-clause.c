#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>

#define THREADS 4
#define N 16

int main ()
{
    int i;
    double start_time;
    start_time = omp_get_wtime();
    
    #pragma omp parallel for schedule(static) num_threads(THREADS)
    for (i = 0; i < N; i++) {
        /* wait for i seconds */
        sleep(i);
        printf("Thread %d has completed iteration %d.\n", omp_get_thread_num( ), i);
    }
    
    /* all threads done */
    printf("All done!\n");
    printf("Execution_time: %f s\n",omp_get_wtime()-start_time);

    return 0;
}

/*
* the schedule clause affects how loop iterations are mapped onto threads
*
* schedule(static[,chunk])	
*   – All iterations are allocated before they execute any loop iterations. Deal-out blocks of iterations of size “chunk” to each thread. By default, this is taken by the parallel for pragma.
*
* schedule(dynamic[,chunk])
*   - Each thread grabs “chunk” iterations off a queue until all iterations have been handled.
*
* schedule(guided[,chunk])	
*   – Threads dynamically grab blocks of iterations. The size of the block starts large and shrinks down to size “chunk” as the calculation proceeds.
*
* schedule(runtime)
*   – Schedule and chunk size taken from the OMP_SCHEDULE environment variable (or the runtime library … for OpenMP 3.0). 
*/

/*
* Increasing the chunk size can reduce the overhead and increase the cache hit rate.
* Reducing the chunk size can allow finer balancing of workloads.
*/