// standard send of number

#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv []) 
{

	int size, rank;
    int x;
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;

	if(rank==0)
	{
		printf("Enter value in master process:\n");
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		fprintf(stdout, "I have sent %d from P0\n",x);
		fflush(stdout);
	}

	else
	{
		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have recieved %d in P1\n",x);
		fflush(stdout);
	}

	MPI_Finalize();

	return 0;
}
