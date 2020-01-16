// square cube

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	int rank,size,x;
	int arr[20];
	int bufsize=sizeof(int)*5+MPI_BSEND_OVERHEAD;
	int *buf=malloc(bufsize);

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Buffer_attach(buf,bufsize);
	MPI_Status status;
	if(rank==0){
		printf("Enter array elements:\n");
		for(int i=0;i<size;i++){
			scanf("%d",&arr[i]);
		}
		
		for(int i=1;i<size;i++){
			MPI_Bsend(&arr[i],1,MPI_INT,i,i,MPI_COMM_WORLD);
		}
		printf("Numbers Sent\n");	
	}
	else{
		MPI_Recv(&x,1,MPI_INT,0,rank,MPI_COMM_WORLD,&status);
		if(rank%2==0){
			printf("Process %d , Number recieved : %d , Result : %d\n",rank,x,x*x);	
		}
		else{
			printf("Process %d , Number recieved : %d , Result : %d\n",rank,x,x*x*x);	
		}
	}
	MPI_Buffer_detach(&buf,&bufsize);
	MPI_Finalize();
	return 0;
}
