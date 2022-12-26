#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
static long num_steps = 1000000;
double steps;
#define NUM_THREADS 8
int main()
{
	int i, nthreads;
	double n, pi, sum[NUM_THREADS] = { 0 };
	steps = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
	{
		double x;
		int id, i, nthreads;
		id = omp_get_thread_num();
		nthreads = omp_get_num_threads();
#pragma omp critical
		{
			for (i = id;i < num_steps;i += nthreads) {
				x = (i + 0.5) * steps;
				sum[id] += 4.0 / (1.0 + x * x);
			}
		}
		for (i = 0, pi = 0;i < nthreads;i++) {
			pi += sum[i] * steps;
		}
	}
	printf("pi value is %f\n", pi);
}