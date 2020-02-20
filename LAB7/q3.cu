#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>


__global__ void func (int *X, int *Y, int *A ) {
	int idx = blockIdx.x*blockDim.x+threadIdx.x;
    printf("idx = %d\n", idx);
    Y[idx] = *A * X[idx] + Y[idx];
}

int main () {
    
    int M,N;
    printf("Blocks M:");
    scanf("%d",&M);
    printf("Threads N:");
    scanf("%d",&N);

    
    // Host copies of the variables
    int X[M], Y[M], A;

    int i, j;
    printf("Enter const. A : ");
    scanf("%d",&A);
    printf("Enter %d elements in X:\n",M*N);
    for (i = 0; i < M*N; ++i) 
        scanf("%d",&X[i]);
    printf("Enter %d elements in Y:\n",M*N);    
    for (i = 0; i < M*N; ++i) 
        scanf("%d",&Y[i]);

    printf("X:\n");
    for (j = 0; j < M*N; ++j) {
        printf("%d\t", X[j]);
    }
    printf("\n");

    printf("Y:\n");
    for (j = 0; j < M*N; ++j) {
        printf("%d\t", Y[j]);
    }
    printf("\n");

    

    // Device copies of the variables
    int *d_x, *d_y , *d_a;

    int size = sizeof(int) * M*N;

    // Allocate memories to device copies of the objects
    cudaMalloc((void**)&d_x, size);
    cudaMalloc((void**)&d_y, size);
    cudaMalloc((void**)&d_a, sizeof(int));

    // Copy inputs to device
    cudaMemcpy(d_x, &X, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, &Y, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_a, &A, sizeof(int), cudaMemcpyHostToDevice);

    // Launch kernel onto the device
    func<<<M, N>>>(d_x, d_y, d_a);

    // Copy the result back to the host
    cudaMemcpy(&Y, d_y, size, cudaMemcpyDeviceToHost);

    // Output
    printf("Y:\n");
    for (j = 0; j < M*N; ++j) {
        printf("%d\t", Y[j]);
    }
    printf("\n");
    
    

    cudaFree(d_x);
    cudaFree(d_y);
    cudaFree(d_a);

	getchar();

    return 0;
}
