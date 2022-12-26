#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char* argv[]) {
	int Pid, numP;
	int sum = 0,temp=0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numP);
	MPI_Comm_rank(MPI_COMM_WORLD, &Pid);

	srand(Pid);
	temp = rand() % 10;
	printf("No. of mangoes picked by robit %d is %d\n", Pid, temp);
	MPI_Reduce(&temp, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (Pid == 0)
		printf("Sum : %d\n", sum);
	MPI_Finalize();
}