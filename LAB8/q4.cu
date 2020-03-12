#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
__global__ void revs(char * d_res , char * d_buffer , int * d_length)
{
    int threadid = threadIdx.x;
    int length = *d_length ;
    d_res[threadid]=d_buffer[length-1-threadid];
    
 }
int main(void)
{

char buffer[100];
char res[100];

printf("\nEnter string :");
gets(buffer);

int length = strlen(buffer) ;

char * d_res ; 
char * d_buffer ; 
int * d_length;

cudaMalloc((void **)&d_res,(length+1) * sizeof(char));
cudaMalloc((void **)&d_buffer,(length+1)*sizeof(char));
 cudaMalloc((void **)&d_length,sizeof(int));

cudaMemcpy(d_buffer,buffer,(length+1)*sizeof(char),cudaMemcpyHostToDevice);
 cudaMemcpy(d_length,&length,sizeof(int),cudaMemcpyHostToDevice);


revs<<<1,length>>>(d_res,d_buffer,d_length);
cudaError_t error = cudaGetLastError();
 if(error!= cudaSuccess)
 {
	 	printf("%s\n",cudaGetErrorString(error));
 }
cudaMemcpy(&res,d_res,sizeof(char) * length,cudaMemcpyDeviceToHost);
res[length]='\0';
printf("Result :%s\n",res);

}
