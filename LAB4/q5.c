// column sum

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int rank,size;
	int arr[100];int arr1[4];
	int arr2[10];
	int x;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(rank==0)
	{
		printf("ENTER THE 4X4 ARRAY:\n");
		for(int i=0;i<16;i++) 
			scanf("%d",&arr[i]);
	}
	
	MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr,4,MPI_INT,arr1,4,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scan(arr1,arr2,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Gather(arr2,4,MPI_INT,arr,4,MPI_INT,0,MPI_COMM_WORLD);
	
	if(rank==0)
		for(int i=0;i<16;i++){ 
			printf("%3d ",arr[i]);
			if(i%4==3) printf("\n");
		}
	MPI_Finalize();
	return 0;
}
