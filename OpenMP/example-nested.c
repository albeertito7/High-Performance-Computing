#include <stdio.h>
#include <omp.h>

/*
* this programs shows how to use the OMP_NUM_THREADS environment variable to control the number of threads
*       on multiple nested levels
*/

int main(void)
{
        omp_set_nested(1); // enables or disables nested parallelism by setting the max-active-levels-var
        omp_set_dynamic(0); // enables or disables dynamic adjustment of the number of threads available for the execution of subsequent parallel regions

        #pragma omp parallel
        {
                #pragma omp parallel
                {
                        #pragma omp single
                        printf("Inner: num_threads=%d\n",omp_get_num_threads());
                }

                #pragma omp barrier
                omp_set_nested(0);
        
                #pragma omp parallel
                {
                        #pragma omp single
                        // even if OMP_NUM_THREADS=4 was set, the following should be print because nesting is disable: Inner: num_threads=1
                        printf("Inner: num_threads=%d\n",omp_get_num_threads());
                }
        
                #pragma omp barrier
                #pragma omp single
                printf("Outer: num_threads=%d\n",omp_get_num_threads());
        }
        
        return 0;
}