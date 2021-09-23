/*
* Internal Control Variables (ICV)
* This example illustrates two ICVs, nthreads-var (controls the number of threads requestesd for parallel regions)
*   and max-active-levels-var (controls de maximum number of nested active parallel region)
*/

#include <omp.h>
#include <stdio.h>

int main()
{
    omp_set_nested(1);
    omp_set_max_active_levels(8);
    omp_set_dynamic(0);
    omp_set_num_threads(2); /* runtime function to request a certain number of threads */
    
    /* 
    * parallel construct 
    * each thread executes a copy of the code within the structured block
    */
    #pragma omp parallel
    {
        omp_set_num_threads(3); /* execution with 3 threads */
        
        #pragma omp parallel
        {
            omp_set_num_threads(8); /* Will this clause affect? */
            #pragma omp single
            {
                printf("Inner: max_active_levels=%d, num_threads=%d, max_threads=%d\n", omp_get_max_active_levels(), omp_get_num_threads(), omp_get_max_threads());
            }
        }
        
    #pragma omp barrier
        #pragma omp single
        {
            printf("Outer: max_active_levels=%d, num_threads=%d, max_threads=%d\n", omp_get_max_active_levels(), omp_get_num_threads(), omp_get_max_threads());
        }
        
    }

    return 0;
}

/* 
* Try to understand the nested parallel regions and think about the possible output
* Let's check then if you were correct by running the program
*/