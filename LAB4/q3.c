// search matrix
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int rank,size,fact=1,factsum;
	int arr[100];int arr1[3];
	int x,count=0,occ;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(rank==0)
	{
		printf("ENTER THE 3X3 ARRAY:\n");
		for(int i=0;i<9;i++) scanf("%d",&arr[i]);
		printf("Enter the Key: \n");
		scanf("%d",&x);
	}
	
	MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr,3,MPI_INT,arr1,3,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<3;i++)
		if(arr1[i]==x) 
			count++;
	
	MPI_Scan(&count,&occ,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	
	if(rank==size-1)
		printf("\nNumber of Occurencess=%d\n",occ);
	
	MPI_Finalize();
	return 0;
}
