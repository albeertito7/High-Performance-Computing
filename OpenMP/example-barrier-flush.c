#include <stdio.h>
#include <omp.h>

/*
* the value x could be either 2 or 5
* depending on the timing of the threads and the implementation of the assignment to x
*/

int main(void)
{
    int x;
    x=2; // global var
    
    #pragma omp parallel num_threads(5)
    {
        if (omp_get_thread_num() == 0) {
            x=5; // the assignment will affect the global scope, as x is not privately specified to omp
        }
        else {
            printf("Thread %d x=%d before barrier\n", omp_get_thread_num(), x);
        }

        /*
        * the barrier contains implicit flushes on all the threads
        */
        #pragma omp barrier
        if (omp_get_thread_num() == 0) {
            printf("Thread %d x=%d after barrier\n", omp_get_thread_num(), x);
        }
        else {
            printf("Thread %d x=%d after barrier\n", omp_get_thread_num(), x);
        }
    
    }
    
    return 0;
}

/*
* the before print, depending on the thread timing, it will get 2 or 5
* but as there's a barrier, the after print always will be 5 for all the threads as the x variable will be updated at that time
*/

/*
* Flush Operation: defines a sequence point at which a thread is guaranteed to see a consistent view of memory
*   - All previous read/writes by this thread have completed and are visible to other threads
*   - No subsequent read/writes by this thread have occurred
*   - A flush operation is analogous to a fence in other shared memory API’s
*/