#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char* argv[]) {
	int Pid, numP;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numP);
	MPI_Comm_rank(MPI_COMM_WORLD, &Pid);

	int send[10] = { 10 }, recv;

	if (Pid == 0) {
		for (int i = 0;i < numP;i++) {
			srand(i);
			send[i] = rand() % 10;
			printf("value %d is send for process %d\n", send[i], i);
		}
	}
	MPI_Scatter(&send, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	printf("process %d recieved %d\n", Pid, recv);
	MPI_Finalize();
}

#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int rank, size;
	int data, gatheredData[100];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand(rank);
	data = rand()%10;
	printf("Process %d sending data %d\n", rank, data);
	
	MPI_Gather(&data, 1, MPI_INT, gatheredData, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("Process %d has gathered data: ", rank);
		for (int i = 0; i < size; i++) {
			printf("%d ", gatheredData[i]);
		}
		printf("\n");
	}

	MPI_Finalize();
	return 0;
}

#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int rank, size;
	int data;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		data = 100;
		printf("Process %d broadcasting data %d\n", rank, data);
	}

	MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("Process %d received data %d\n", rank, data);

	MPI_Finalize();
	return 0;
}
