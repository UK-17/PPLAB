// incremental passing

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv []) {

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		
		int k;

		fprintf(stdout, "[P%d] Enter a number : ", rank);
		scanf("%d",&k);

		k += 1;

		// Send to ID = 1
		MPI_Send(&k, 1, MPI_INT, rank + 1, rank, MPI_COMM_WORLD);
		fprintf(stdout, "\nP[%d] sent: %d.\n", rank, k);

		// Receive from ID = N - 1
		MPI_Recv(&k, 1, MPI_INT, size - 1, size - 1, MPI_COMM_WORLD, &status);
		fprintf(stdout,"P[%d] recv: %d.\n", rank, k);

	} else {
		
		int k;
		// Receive from ID - 1
		MPI_Recv(&k, 1, MPI_INT, rank - 1, rank - 1, MPI_COMM_WORLD, &status);
		fprintf(stdout,"P[%d] recv: %d.\n", rank, k);

		k += 1;
		// Send to (ID + 1) % size
		MPI_Send(&k, 1, MPI_INT, (rank + 1) % size, rank, MPI_COMM_WORLD);
		fprintf(stdout, "P[%d] sent: %d.\n", rank, k);


	} 

	MPI_Finalize();
}
