
#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE 0x100000

int main (void) {

	int i;

	int SIZE;

	printf("Enter Array size: ");
	scanf(" %d",&SIZE);
	printf("Enter %d elements:\n",SIZE);

	// 0. Create and initialize two vectors

	int *A = (int *)malloc(sizeof(int) * SIZE);

	for (i = 0; i < SIZE; ++i) {
		scanf("%d",&A[i]);
	}

	// 1. Load the kernel code

	FILE *kernel_code_file = fopen("oct.cl", "r");
	if (kernel_code_file == NULL) {
		printf("Kernel loading failed.");
		exit(1);
	}

	char *source_str = (char *)malloc(MAX_SOURCE_SIZE);
	size_t source_size = fread(source_str, 1, MAX_SOURCE_SIZE, kernel_code_file);

	fclose(kernel_code_file);

	// 2. Get platform and device information

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;

	cl_uint ret_num_devices, ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &ret_num_devices);


	// 3. Create an OpenCL context

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);


	// 4. Create a command queue

	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);


	// 5. Create memory buffers on the device for each vector A and B

	cl_mem mem_obj_a = clCreateBuffer(context, CL_MEM_READ_ONLY, SIZE * sizeof(int), NULL, &ret);

	cl_mem mem_obj_b = clCreateBuffer(context, CL_MEM_WRITE_ONLY, SIZE * sizeof(int), NULL, &ret);


	// 6. Copy the list A to the respective memory buffers

	ret = clEnqueueWriteBuffer(command_queue, mem_obj_a, CL_TRUE, 0, SIZE * sizeof(int), A, 0, NULL, NULL);


	// 7. Create a program from kernel source

	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);


	// 8. Build the kernel program

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);


	// 9. Create the OpenCL kernel object

	cl_kernel kernel = clCreateKernel(program, "octal_conv", &ret);


	// 10. Set the arguments of the kernel dode

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&mem_obj_a);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&mem_obj_b);


	// 11. Execute the kernel on device

	size_t global_item_size = SIZE;
	size_t local_item_size = 1;

	// cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

	ret = clFinish(command_queue);


	// 12. Read the memory buffer C on the device to the local variable C, and display

	int *B = (int *)malloc(sizeof(int) * SIZE);

	ret = clEnqueueReadBuffer(command_queue, mem_obj_b, CL_TRUE, 0, SIZE * sizeof(int), B, 0, NULL, NULL);

	for (i = 0; i < SIZE; ++i) {
		printf("%6d <10> = %6d <8>\n", A[i], B[i]);
	}


	// 13. Clean up

	clFlush(command_queue);
	clReleaseKernel(kernel);
	clReleaseProgram(program);

	clReleaseMemObject(mem_obj_a);
	clReleaseMemObject(mem_obj_b);

	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);

	free(A);
	free(B);

	int d;
	scanf(" %d", &d);

	return 0;

}

//oct.cl

__kernel void octal_conv (__global int *A, __global int *B) {

	int i = get_global_id(0);

	int dec = A[i];
	int oct = 0, r, p = 1;
	while (dec != 0) {
		r = dec % 8;
		oct = oct + p * r;
		dec /= 8;
		p *= 10;
	}
	B[i] = oct;

}

