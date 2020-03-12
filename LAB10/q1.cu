#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>
#include<unistd.h>
#define BLOCK_WIDTH 2
#define TILE_WIDTH 2
#define WIDTH 4

__device__ int getTid()
{
	int blockSkip=(blockIdx.y*gridDim.x*blockDim.x*blockDim.y);
	int rowSkip=(threadIdx.y*gridDim.x*blockDim.x);
	int rowDisplacement=(blockIdx.x*blockDim.x)+threadIdx.x;
	int tid=blockSkip+rowSkip+rowDisplacement;
	return tid;
}

__global__ void MatMulElement(int *a,int *b,int *c)
{
	int tid=getTid();
	int rId=tid%4;
	int cId=tid-(tid%4);
	int sum=0;
	for(int i=0;i<4;i++)
		sum+=a[cId+i]*b[rId+4*i];
	
	c[tid]=sum;
}


int main()
{
	int *matA,*matB,*res_matrix;
	int *da,*db,*dc;
	int m,n;
	
	m=n=WIDTH;
	int size=sizeof(int)*WIDTH*WIDTH;
	
	printf("Enter the matrix A elements(4x4):\n");
	matA=(int*)malloc(size);
	for(int i=0;i<WIDTH*WIDTH;i++)
		scanf("%d",&matA[i]);
	
	printf("Enter the matrix B elements(4x4):\n");
	matB=(int*)malloc(size);
	for(int i=0;i<WIDTH*WIDTH;i++)
		scanf("%d",&matB[i]);
	
	res_matrix=(int*)malloc(size);
	
	cudaMalloc((void**)&da,size);
	cudaMalloc((void**)&db,size);
	cudaMalloc((void**)&dc,size);
	
	cudaMemcpy(da,matA,size,cudaMemcpyHostToDevice);
	cudaMemcpy(db,matB,size,cudaMemcpyHostToDevice);
	
	int NumBlocks=WIDTH/BLOCK_WIDTH;
	dim3 grid (NumBlocks,NumBlocks);
	dim3 block (BLOCK_WIDTH,BLOCK_WIDTH);
	
	MatMulElement<<<grid,block>>>(da,db,dc);
	
	cudaMemcpy(res_matrix,dc,size,cudaMemcpyDeviceToHost);
	
	printf("Result :\n");
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
			printf("%d\t",res_matrix[i*n+j]);
		printf("\n");
	}	
		printf("\n");
	
	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	
	free(matA);
	free(matB);
	free(res_matrix);
	
	return 0;
}
