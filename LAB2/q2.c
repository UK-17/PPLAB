#include "mpi.h"
#include <stdio.h>
// master sends to slaves number

#include <stdlib.h>

#define SIZE sizeof(int)

int main (int argc, char *argv []) {

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int *number = (int *)malloc(SIZE);
	
	int i;

	if (rank == 0) {

		*number = rand() % 10 + 1;
		for (i = 1; i < size; ++i) {
			printf("[%d]Sent to [%d]: %d\n", rank, i, *number);
			
			MPI_Send(number, SIZE, MPI_INT, i, 100 + i, MPI_COMM_WORLD);
		}

	} 

	else {
            		
		
		MPI_Recv(number, SIZE, MPI_INT, 0, 100 + rank, MPI_COMM_WORLD, &status);

		printf("[%d] Recv: %d\n", rank, *number);

	}

	MPI_Finalize();
}
