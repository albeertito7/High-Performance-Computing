#include <omp.h>
#include <stdio.h>

int main(void)
{    
    /*
    * The default value depends of the OpenMP implementation.
    * The call to the omp_set_dynamic with zero argument allows the OpenMP implementation to choose
    *   any number of threads between 1 and 20.
    * omp_set_dynamic with argument 0 disables the dynamic adjustment of the number of threads.
    * It's a good practice begin the program with an omp_set_dynamic call.
    */
    omp_set_dynamic(0);

#pragma omp parallel num_threads(20)  
    printf("Thread=%d\n",omp_get_thread_num());
    
    return 0;
}