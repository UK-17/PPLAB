// non vowels

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

	int rank,size;
	int count = 0;
	int b[100] = {0};

	int i, n, l;
	
	char str[100], c[100];
	
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) 
	{

		n = size;

		printf("Enter the string: ");
		scanf("%s",str);

		l = strlen(str) / n;
		
	}

	MPI_Bcast(&l, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Scatter(str, l, MPI_CHAR, c, l, MPI_CHAR, 0, MPI_COMM_WORLD);

	count = 0;
	for (i = 0; i < l; ++i) {
		if (strchr("aeiouAEIOU", c[i]) == NULL)
			count += 1;
	}

	printf("P[%d] NON-VOWELS = %d\n", rank, count);

	MPI_Gather(&count, 1, MPI_INT, b, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) 
	{
		
		int t_count = 0;
		for (i = 0; i < n; i++)
			t_count += b[i];
		printf("TOTAL (NON-VOWELS) = %d\n", t_count);

	}

	MPI_Finalize();
}
