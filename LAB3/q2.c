//average

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

	int rank,size;
	int i, n, m;

	float avg = 0;
	float total[100];
    int arr[100],buf[100];
	
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		n = size;
		printf("'n' = %d\n",n);
		printf("Enter 'm': ");
		scanf("%d",&m);

		printf("Enter %d x %d = %d elements:\n", n, m, n*m);
		for (i = 0; i < n * m; ++i) {
			scanf("%d",&arr[i]);
		}
		
	}

	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(arr, m, MPI_INT, buf, m, MPI_INT, 0, MPI_COMM_WORLD);

	for (i = 0; i < m; ++i) 
		avg += buf[i];
	

	avg /= m;
	printf("P[%d] Average = %.2f\n", rank, avg);

	MPI_Gather(&avg,1,MPI_FLOAT,total,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if (rank == 0) {
		
		float t_avg = 0;
		for (i = 0; i < n; i++)
			t_avg += total[i];
		t_avg /= n;
		printf("Total average = %.2f\n", t_avg);

	}

	MPI_Finalize();
}
