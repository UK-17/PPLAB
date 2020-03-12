#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void kernel(int *a,int *b,int *c,int n){
	int id1=threadIdx.x;
	int id2=blockIdx.x;
	int pos=id2*n+id1;
	c[pos]=a[pos]+b[pos];
}

int main(){
	int *a,*b,*c;
	int *d_a,*d_b,*d_c;
	printf("Enter the order of the matrix: ");
	int n;scanf("%d",&n);
	int size=sizeof(int)*n*n;
	a=(int *)malloc(size);
	b=(int *)malloc(size);
	c=(int *)malloc(size);

	printf("Enter the Matrix A: \n");
	for(int i=0;i<n*n;i++){
		scanf("%d",&a[i]);
	}
	printf("\n");

	printf("Enter the Matrix B: \n");
	for(int i=0;i<n*n;i++){
		scanf("%d",&b[i]);
	}
	printf("\n");

	cudaMalloc((void **)&d_a,size);
	cudaMalloc((void **)&d_b,size);
	cudaMalloc((void **)&d_c,size);

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);

	kernel<<<n,n>>>(d_a,d_b,d_c,n);

	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
	printf("Result Matrix is: \n");
	for(int i=0;i<n*n;i++){
		if(i%n==0) printf("\n");
		printf("%5d ",c[i]);
	}
	printf("\n");

	getchar();
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
