#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>


__global__ void trig (float *input, float *output) {
	int idx = blockIdx.x*blockDim.x+threadIdx.x;
    printf("idx = %d\n", idx);
    output[idx] = sin(input[idx]);
}

int main () {
    
    int M,N;
    printf("Blocks M:");
    scanf("%d",&M);
    printf("Threads N:");
    scanf("%d",&N);

    
    // Host copies of the variables
    float input[M*N], output[M*N];

    int i, j;
    printf("Enter %d elements:\n",M*N);
    for (i = 0; i < M*N; ++i) 
        scanf("%f",&input[i]);
   

    // Device copies of the variables
    float *d_a, *d_b;

    int size = sizeof(float) * M*N;

    // Allocate memories to device copies of the objects
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    

    // Copy inputs to device
    cudaMemcpy(d_a, &input, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, &output, size, cudaMemcpyHostToDevice);

    // Launch kernel onto the device
    trig<<<M, N>>>(d_a, d_b);

    // Copy the result back to the host
    cudaMemcpy(&output, d_b, size, cudaMemcpyDeviceToHost);

    // Output
    printf("X     :");
    for (j = 0; j < M*N; ++j) 
        printf("\t%f", input[j]);
    
    printf("\n");

    printf("sin(x):");
    for (j = 0; j < M*N; ++j) 
        printf("\t%f", output[j]);
    
    printf("\n");


    cudaFree(d_a);
    cudaFree(d_b);


	getchar();

    return 0;
}
