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

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char* argv[]) {
	int Pid,buf[1000] ,numP;
	int sum = 0,temp=0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numP);
	MPI_Comm_rank(MPI_COMM_WORLD, &Pid);
	MPI_Status stat;

	for (int i = 0;i < numP;i++)
		buf[i] = rand() % 10;

	if (Pid != 0)
		MPI_Send(&buf[Pid],1,MPI_INT,0,0,MPI_COMM_WORLD);

	if (Pid == 0) {
		printf("Robot 0 picked %d mangoes\n", buf[0]);
		sum += buf[0];
		for (int i = 1;i < numP;i++) {
			MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &stat);
			sum += temp;
			printf("Robot %d picked %d mangoes\n", i, temp);
		}
		printf("Sum : %d\n", sum);
	}
	
		
	MPI_Finalize();
}
