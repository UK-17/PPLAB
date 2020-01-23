// concat

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv [] ) 
{

	int rank, size;

	float avg = 0;
	char b[100], str1[100], str2[100], buf1[100], buf2[100], mix[100];

	int i,m;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (rank == 0) 
	{ 

		printf("Enter string 1: ");
		scanf("%s",str1);
		printf("Enter string 2: ");
		scanf("%s",str2);

		m = strlen(str1) / size;
	}
	
	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Scatter(str1, m, MPI_CHAR, buf1, m, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Scatter(str2, m, MPI_CHAR, buf2, m, MPI_CHAR, 0, MPI_COMM_WORLD);
	
	for (i = 0; i <= 2 * m; i += 2) 
	{
		mix[i] = buf1[i/2];
		mix[i+1] = buf2[i/2];
	}
	
	
	MPI_Gather(mix, 2*m, MPI_CHAR, b, 2*m, MPI_CHAR, 0, MPI_COMM_WORLD);
	
	if (rank == 0) 
	 printf("RESULT: %s\n",b);
	

	MPI_Finalize();
}
