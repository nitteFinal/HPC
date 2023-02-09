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

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
void main() {
    int num, i;
    printf("Enter the number of steps : ");
    scanf_s("%d", &num);
    time_t st, et;
    st = clock();
    double step = 1.0 / (double)num, pi = 0.0;
    omp_set_num_threads(num);
#pragma omp parallel for
    for (i = 0;i < num;i++) {
        double x = (i + 0.5) * step;
        double local_pi = (4.0 * step) / (1 + x * x);
#pragma omp critical
        pi += local_pi;
    }
    et = clock();
    printf("Time Taken : %lf\n", (double)((double)(et - st) / CLOCKS_PER_SEC));
    printf("Value of Pi = %lf\n", pi);
}
