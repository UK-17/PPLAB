//fact series sum

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int fact(int n) {
	if (n<=1)
		return 1;
	else
		return n*fact(n-1);
}

int main(int argc,char* argv[])
{
	int rank, size;
	int i = 0;
	int k = 0,fac=1;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	for (i=1;i<=rank+1;i++) 
		fac = fac*i;
		
	MPI_Scan(&fac,&k,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	
	if (rank == size-1) 
	 printf("%d\n",k);
	
	
	
	MPI_Finalize();
	return 0;
}
