/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 08:12:19 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/14 16:38:01 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>	
#include <stdlib.h>

#include <OpenCL/opencl.h>

#define MAX_SOURCE_SIZE (0x100000)	


t_ocl		*init_kernel(int size_x, int size_y, const char *name_file)
{
	(void)size_x;
	(void)size_y;
	(void)name_file;

	t_ocl				*ocl;
	FILE				*fp;
//	const char name_file[] = "src_cl/data_parallel.cl";
	size_t				source_size;
	char 				*source_str;
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;

	if (!(ocl = (t_ocl*)ft_memalloc(sizeof(t_ocl))))
		return (NULL);
	/* Load kernel source file */
	fp = fopen(name_file, "r");
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
	ocl->context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	/* Create command queue */
	ocl->command_queue = clCreateCommandQueue(ocl->context, device_id, 0, &ret);
	/* Create kernel program from source file*/
	ocl->program = clCreateProgramWithSource(ocl->context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);	
	ret = clBuildProgram(ocl->program, 1, &device_id, NULL, NULL, NULL);
	/* Create data parallel OpenCL kernel */	
	ocl->kernel = clCreateKernel(ocl->program, "test_image", &ret);
	free(source_str);
	return (ocl);
}

t_mem_ocl	*init_mem_ocl(t_win *w, t_ocl *ocl)
{
	t_mem_ocl	*mem;
	int 		i;
	int			j;
	cl_int		ret;
	(void)(i);
	(void)(j);

	if (!(mem = (t_mem_ocl*)ft_memalloc(sizeof(t_mem_ocl))))
		return (NULL);
	/*
	mem->A = (float *)malloc(4*4*sizeof(float));
	mem->B = (float *)malloc(4*4*sizeof(float));
	mem->C = (float *)malloc(4*4*sizeof(float));
	for (i=0; i < 4; i++) {
		for (j=0; j < 4; j++) {
			mem->A[i*4+j] = i*4+j+1;
			mem->B[i*4+j] = j*4+i+1;
		}	
	}
	mem->Amobj = clCreateBuffer(ocl->context, CL_MEM_READ_ONLY, 4*4*sizeof(float), NULL, &ret);
	mem->Bmobj = clCreateBuffer(ocl->context, CL_MEM_READ_ONLY, 4*4*sizeof(float), NULL, &ret);
	mem->Cmobj = clCreateBuffer(ocl->context, CL_MEM_WRITE_ONLY, 4*4*sizeof(float), NULL, &ret);
	*/


	mem->img_data = (int*)w->data;
	mem->ocl_time = clCreateBuffer(ocl->context, CL_MEM_READ_ONLY, sizeof(int), NULL, &ret);
	mem->ocl_data = clCreateBuffer(ocl->context, CL_MEM_WRITE_ONLY, (w->size_x * w->size_y) * sizeof(int), NULL, &ret);
	return (mem);
}


int		main_while_ocl(t_mem_ocl *mem, t_ocl *ocl, t_win *w)
{
	static	int count = 0;
	int	i;
	int	j;
	cl_int	ret;
	size_t	global_item_size;
	size_t	local_item_size;
	(void)i;
	(void)j;

	global_item_size = w->size_x * w->size_y;
	local_item_size = 1;
	
/*
	for (i=0; i < 4; i++) {
		for (j=0; j < 4; j++) {
			mem->A[i*4+j] = i*4+j+1 + count;
			mem->B[i*4+j] = j*4+i+1 + count;
		}
	}

	ret = clEnqueueWriteBuffer(ocl->command_queue, mem->Amobj, CL_TRUE, 0, 4*4*sizeof(float), mem->A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(ocl->command_queue, mem->Bmobj, CL_TRUE, 0, 4*4*sizeof(float), mem->B, 0, NULL, NULL);

	ret = clSetKernelArg(ocl->kernel, 2, sizeof(cl_mem), (void *)&(mem->Cmobj));
*/

	ret = clEnqueueWriteBuffer(ocl->command_queue, mem->ocl_time
			, CL_TRUE, 0, sizeof(int), &count, 0, NULL, NULL);
	ret = clSetKernelArg(ocl->kernel, 0, sizeof(cl_mem), (void *)&(mem->ocl_time));
	ret = clSetKernelArg(ocl->kernel, 1, sizeof(cl_mem), (void *)&(mem->ocl_data));
	/* Execute OpenCL kernel as data parallel */
	ret = clEnqueueNDRangeKernel(ocl->command_queue, ocl->kernel, 1, NULL,
			&global_item_size, &local_item_size, 0, NULL, NULL);

	/* Transfer result to host */
	ret = clEnqueueReadBuffer(ocl->command_queue, mem->ocl_data, CL_TRUE, 0,
			(w->size_x * w->size_y) * sizeof(int), mem->img_data, 0, NULL, NULL);
	
	mlx_put_image_to_window(w->e->mlx, w->win, w->img, 0, 0);
//	printf("---------------------------------------------\n");
	count++;
	return (0);
}



/*
void		actual_ocl_data(t_mem_ocl *mem)
{
	(void)mem;
}

*/
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
	ret = clReleaseMemObject((*mem)->Amobj);
	ret = clReleaseMemObject((*mem)->Bmobj);
	ret = clReleaseMemObject((*mem)->Cmobj);
	free((*mem)->A);
	free((*mem)->B);
	free((*mem)->C);
	*mem = NULL;
	return (1);
}
