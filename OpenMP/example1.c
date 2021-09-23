/*
* Data Scoping
* Every thread has its own execution context (address space containing all its variables).
* Variables may either be shared or private.
* Any variable existed before a parallel region still exist inside and is shared by default.
* Each thread can have its own private variables also.
* Three ways to make private variables:
*   - using a PRIVATE CLAUSE in the OMP parallel directive to privatize an existing variable.
*   - the index variable of a worksharing loop is made private automatically.
*   - local variables in a subrutine called from a parallel region are private to each calling thread.
*/

#include <omp.h>
#include <stdio.h>

#define  N 10000 // arrays length

void main()
{
    /* shared variables */
    double start_time,run_time; 
    int i;
    int a[N],b[N],c[N];

    start_time=omp_get_wtime();

    #pragma omp parallel num_threads(1)
    {
        /* private variables */
        int bstart, bend, blen, numth, tid, i;
        numth=omp_get_num_threads();
        tid=omp_get_thread_num();
        blen=N/numth;

        if(tid < N % numth) {
            blen++;
            bstart=blen*tid;
        }
        else {
            bstart=blen*tid+N%numth;
        }

        bend=bstart+blen-1;
        for(i=bstart; i<=bend; i++) // building the arrays
        {
            c[i]=i;
            b[i]=i;
        }

        for(i=bstart; i<=bend; i++) { // simple loop that adds to arrays
            a[i]=b[i]+c[i];
        }
    }

    run_time=omp_get_wtime()-start_time;

    printf("Execution Time=%lf\n", run_time);
    printf("Value of Dynamic=%d\n", omp_get_dynamic());
}