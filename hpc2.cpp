#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
int main()
{
	int i, j;
	int a[10][10] = { 0,0 };
	int x[10] = { 0 };
	int c[10] = { 0 };
	srand(time(0));
	static int sum = 0;
	int n ;
	n = rand() % 10;
	for (i = 0;i < n;i++) {
		c[i] = rand() % 10;
		for (j = 0;j < c[i];j++) {
			a[i][j] = rand() % 1000;
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	double start = omp_get_wtime();
#pragma omp parallel for
	{
		for (i = 0;i < n;i++) {
			for (j = 0;j < n;j++) {
				x[i] += a[i][j];
			}
#pragma omp critical
			{
				sum += x[i];
			}
		}
		printf("sum: %d\n", sum);
	}
	printf("\ntime taken %f\n", omp_get_wtime() - start);
 }