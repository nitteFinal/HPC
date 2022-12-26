#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main() {
	int i,j,n;
	
	n = rand() % 10 ;

	int a[100][100], x[100];
	static int y[100];
	printf("n: %d\n", n);
	printf("A\n");
	for ( i = 0;i < n;i++) {
		for ( j = 0;j < n;j++) {
			a[i][j] = rand() % 10;
			printf("%d ", a[i][j]);
		}
	}

	printf("\nX\n");
	for ( i = 0;i < n;i++) {
		x[i] = rand() % 10;
		printf("%d ", x[i]);
	}
	printf("\n");
	double start = omp_get_wtime();

	omp_set_num_threads(n);
#pragma omp parallel 
	{
		for ( i = 0;i < n;i++) {
			for ( j = 0;j < n;j++) {
				y[i] += a[i][j] * x[j];
			}
		}
		printf("%d \n", y[omp_get_thread_num()]);
		
	}
	printf("\ntime taken %f\n", omp_get_wtime() - start);
	
}