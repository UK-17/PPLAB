#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>


__global__ void add (int *A, int *B, int *C) {
	int idx = blockIdx.x*blockDim.x+threadIdx.x;
    printf("idx = %d\n", idx);
    C[idx] = A[idx] + B[idx];
}

int main () {
    
    int M,N;
    printf("Blocks M:");
    scanf("%d",&M);
    printf("Threads N:");
    scanf("%d",&N);

    
    // Host copies of the variables
    int A[M*N], B[M*N], C[M*N];

    int i, j;
    printf("Enter %d elements in A:\n",M*N);
    for (i = 0; i < M*N; ++i) 
        scanf("%d",&A[i]);
    printf("Enter %d elements in B:\n",M*N);    
    for (i = 0; i < M*N; ++i) 
        scanf("%d",&B[i]);
    

    // Device copies of the variables
    int *d_a, *d_b, *d_c;

    int size = sizeof(int) * M*N;

    // Allocate memories to device copies of the objects
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    // Copy inputs to device
    cudaMemcpy(d_a, &A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, &B, size, cudaMemcpyHostToDevice);

    // Launch kernel onto the device
    add<<<M, N>>>(d_a, d_b, d_c);

    // Copy the result back to the host
    cudaMemcpy(&C, d_c, size, cudaMemcpyDeviceToHost);

    // Output
    printf("A:\n");
    for (j = 0; j < M*N; ++j) {
        printf("%d\t", A[j]);
    }
    printf("\n");

    printf("B:\n");
    for (j = 0; j < M*N; ++j) {
        printf("%d\t", B[j]);
    }
    printf("\n");

    printf("A + B:\n");
    for (j = 0; j < M*N; ++j) {
        printf("%d\t", C[j]);
    }
    printf("\n");

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

	getchar();

    return 0;
}
