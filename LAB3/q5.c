// odd even

#include <mpi.h>
#include <stdio.h>

int main(int argc,char* argv[])

{
	int rank,size;
	int N,M;
	int A[10],B[10];
	int c,i,l;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(rank==0)
	{
		M=size;
		printf("No of P : %d\n",M);
		printf("Enter array size:");
		scanf("%d",&N);
		printf("Enter %d values:\n",N);
		for(i=0;i<N;i++)
			scanf("%d",&A[i]);
		l=N/M;
	}
	
	MPI_Bcast(&l, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(A,l,MPI_INT,B,l,MPI_INT,0,MPI_COMM_WORLD);
	
	for(int i=0;i<l;i++)
	{
		if(B[i]%2==0)
			B[i]=1;
		else
			B[i]=0;
	}
	
	
	MPI_Gather(B,l,MPI_INT,A,l,MPI_INT,0,MPI_COMM_WORLD);
	
	if(rank==0)
	{
		int even=0,odd=0;
		printf("Result:\n");
		for(i=0;i<N;i++)
			{
				printf("%d\t",A[i]);
				if(A[i]==0)
					odd++;
				else
					even++;
			}
			printf("\nEVEN:%d\nODD:%d\n",even,odd);
	}
	
	MPI_Finalize();
	return 0;
}
