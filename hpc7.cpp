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