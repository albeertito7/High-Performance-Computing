#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;

int main ()
{
	int i;
	double x, pi, sum = 0.0;
	double start_time, run_time;

	step = 1.0/(double) num_steps;//Width of the rectangle
	
	start_time = omp_get_wtime();

	//sum of the rectangles
	for (i=1; i <= num_steps; i++) {
		x = (i-0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}

	pi = step * sum; //Multiply by the width of the rectangle
	run_time = omp_get_wtime() - start_time;
	printf("\n pi with %d steps is %f in %f seconds ",num_steps,pi,run_time);

	return 0;
}