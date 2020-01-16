// hello world
#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv []) {

	int size, rank;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank % 2 == 0) {
		printf("%d. HELLO\n", rank);
	} else {
		printf("%d. WORLD\n", rank);	
	}

	MPI_Finalize();
}
