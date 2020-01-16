// prime nos
#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv []) {

	int size, rank;
	int i, Number, count;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank % 2 == 0) 
  {
		for(Number = 1; Number <= 50; Number++)
      {
         count = 0;
         for (i = 2; i <= Number/2; i++)
          {
  	        
  	        if(Number%i == 0)
  	        {
     	      count++;
  	          break;
	        }
          
          }  
    
    if(count == 0 && Number != 1 )
       printf(" P%d prints %d\n", rank, Number);
      
     
     }
  } 

	else 
	{
		for(Number = 51; Number <= 100; Number++)
      {
         count = 0;
         for (i = 2; i <= Number/2; i++)
          {
  	        
  	        if(Number%i == 0)
  	        {
     	      count++;
  	          break;
	        }
          
          }  
    
    if(count == 0 && Number != 1 )
       printf(" P%d prints %d\n", rank, Number);
      
     
     }	
	}

	MPI_Finalize();
}
