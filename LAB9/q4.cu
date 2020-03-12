#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void kernel(int *a,int *c,int m,int n){
	int id1=threadIdx.x;
	int id2=blockIdx.x;
	int pos=id2*n+id1;
	if((id2==0||id2==m-1)||(id1==0||id1==n-1)) c[pos]=a[pos];
	else{
		int num=a[pos];int f=1;
		int co=0;
		do{
			int d=num%2;
			co=co+(1-d)*f;
			f=f*10;
			num=num/2;
		}while(num!=0);
		c[pos]=co;
	}
}

int main(){
	int *a,*b,*c;
	int *d_a,*d_b,*d_c;
	printf("Enter N: ");
	int n;scanf("%d",&n);
	printf("Enter M: ");
	int m;scanf("%d",&m);
	int size=sizeof(int)*n*m;
	a=(int *)malloc(size);
	b=(int *)malloc(size);
	c=(int *)malloc(size);

	printf("Enter the Matrix A: \n");
	for(int i=0;i<n*m;i++){
		scanf("%d",&a[i]);
	}
	printf("\n");

	cudaMalloc((void **)&d_a,size);
	cudaMalloc((void **)&d_b,size);
	cudaMalloc((void **)&d_c,size);

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);

	kernel<<<m,n>>>(d_a,d_c,m,n);

	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
	printf("Result Matrix is: \n");
	for(int i=0;i<m*n;i++){
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
