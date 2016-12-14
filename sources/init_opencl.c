/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 08:12:19 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/14 09:50:37 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>	
#include <stdlib.h>

#include <OpenCL/opencl.h>

#define MAX_SOURCE_SIZE (0x100000)	


t_ocl		init_kernel(int size_x, int size_y, const char *name_file)
{
	(void)e;
	(void)size_x;
	(void)size_y;
	(void)name_file;

	t_ocl	*ocl;
	FILE	*fp;
//	const char file_name[] = "src_cl/data_parallel.cl";
	size_t	source_size;
	char 	*source_str;

	if (!(ocl = (t_ocl*)ft_memalloc(sizeof(t_ocl))))
		return (NULL);
	/* Load kernel source file */
	fp = fopen(file_name, "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");	
		exit(1);
	}	
	source_str = (char *)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
	/* Get Platform/Device Information */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);	
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	/* Create OpenCL Context */
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	/* Create command queue */
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	/* Create kernel program from source file*/
	program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);	
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	/* Create data parallel OpenCL kernel */	
	kernel = clCreateKernel(program, "dataParallel", &ret);



	return (ocl);
}

t_mem_ocl	*init_mem_ocl(t_ocl *ocl, int size_x, int size_y)
{
	t_mem_ocl	*mem;
	int i, j;

	(void) ocl;
	(void)size_x;
	(void)size_y;
	if !(mem = (t_mem_ocl*)ft_memalloc(sizeof(t_mem_ocl)))
		return (NULL);
	mem->A = (float *)malloc(4*4*sizeof(float));
	mem->B = (float *)malloc(4*4*sizeof(float));
	mem->C = (float *)malloc(4*4*sizeof(float));
	/* Initialize input data */
	for (i=0; i < 4; i++) {
		for (j=0; j < 4; j++) {
			A[i*4+j] = i*4+j+1;
			B[i*4+j] = j*4+i+1;
		}	
	}	
	mem->Amobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 4*4*sizeof(float), NULL, &ret);
	mem->Bmobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 4*4*sizeof(float), NULL, &ret);
	mem->Cmobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 4*4*sizeof(float), NULL, &ret);

	/* Copy input data to the memory buffer */
	ret = clEnqueueWriteBuffer(command_queue, Amobj, CL_TRUE, 0, 4*4*sizeof(float), A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, Bmobj, CL_TRUE, 0, 4*4*sizeof(float), B, 0, NULL, NULL);

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&Amobj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&Bmobj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&Cmobj);

	return (mem);
}

int	init_opencl(t_env *e, int size_x, int size_y)
{
	(void)size_x;
	(void)size_y;
	(void)e;


	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;

	cl_mem Amobj = NULL;	
	cl_mem Bmobj = NULL;	
	cl_mem Cmobj = NULL;	
	float *A;
	float *B;
	float *C;


	cl_program program = NULL;
	cl_kernel kernel = NULL;	
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;

	int i, j;
	A = (float *)malloc(4*4*sizeof(float));
	B = (float *)malloc(4*4*sizeof(float));
	C = (float *)malloc(4*4*sizeof(float));

	/* Initialize input data */
	for (i=0; i < 4; i++) {
		for (j=0; j < 4; j++) {
			A[i*4+j] = i*4+j+1;
			B[i*4+j] = j*4+i+1;
		}	
	}	



	FILE *fp;
	const char file_name[] = "src_cl/data_parallel.cl";
	size_t source_size;
	char *source_str;

	/* Load kernel source file */
	fp = fopen(file_name, "r");
	if (!fp) {
		fprintf(stderr, "Failed to load kernel.\n");	
		exit(1);
	}	
	source_str = (char *)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);


	/* Get Platform/Device Information */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);	
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

	/* Create OpenCL Context */
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	/* Create command queue */
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

	/* Create Buffer Object */
	Amobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 4*4*sizeof(float), NULL, &ret);
	Bmobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 4*4*sizeof(float), NULL, &ret);
	Cmobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 4*4*sizeof(float), NULL, &ret);

	/* Copy input data to the memory buffer */
	ret = clEnqueueWriteBuffer(command_queue, Amobj, CL_TRUE, 0, 4*4*sizeof(float), A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, Bmobj, CL_TRUE, 0, 4*4*sizeof(float), B, 0, NULL, NULL);


	
	/* Create kernel program from source file*/
	program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);	
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	/* Create data parallel OpenCL kernel */	
	kernel = clCreateKernel(program, "dataParallel", &ret);

	/* Set OpenCL kernel arguments */
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&Amobj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&Bmobj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&Cmobj);


///////////////////////
	size_t global_item_size = 4;
	size_t local_item_size = 1;

	/* Execute OpenCL kernel as data parallel */
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
			&global_item_size, &local_item_size, 0, NULL, NULL);

	/* Transfer result to host */
	ret = clEnqueueReadBuffer(command_queue, Cmobj, CL_TRUE, 0, 4*4*sizeof(float), C, 0, NULL, NULL);

	/* Display Results */
	for (i=0; i < 4; i++) {
		for (j=0; j < 4; j++) {
			printf("%7.2f ", C[i*4+j]);
		}	
		printf("\n");
	}	
///////////////////////


	/* Finalization */
	ret = clFlush(command_queue);	
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);

	ret = clReleaseMemObject(Amobj);
	ret = clReleaseMemObject(Bmobj);
	ret = clReleaseMemObject(Cmobj);

	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);	

	free(source_str);

	free(A);
	free(B);
	free(C);
	return (0);
}

void		actual_ocl_data(t_mem_ocl *mem)
{
	(void)meme;
}

int			destroy_ocl(t_ocl **ocl)
{
	cl_int ret;

	if (!ocl || !*ocl)
		return (0);
	ret = clFlush((*ocl)->command_queue);	
	ret = clFinish((*ocl)->command_queue);
	ret = clReleaseKernel((*ocl)->kernel);
	ret = clReleaseProgram((*ocl)->program);
	ret = clReleaseCommandQueue((*ocl)->command_queue);
	ret = clReleaseContext((*ocl)->context);	
	*ocl = NULL;
	return (1);
}

int	destroy_mem_ocl(t_mem_ocl **mem)
{
	
	cl_int ret;

	if (!mem || !*mem)
		return (0);
	ret = clReleaseMemObject((*ocl)->Amobj);
	ret = clReleaseMemObject((*ocl)->Bmobj);
	ret = clReleaseMemObject((*ocl)->Cmobj);
	*ocl = NULL;
	free(A);
	free(B);
	free(C);
	return (1);
}


