/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 08:12:19 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/16 08:42:37 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>	
#include <stdlib.h>

#include <OpenCL/opencl.h>



t_ocl		*init_kernel(int size_x, int size_y, const char *name_file)
{
	(void)size_x;
	(void)size_y;
	(void)name_file;

	t_ocl				*ocl;
	FILE				*fp;
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
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
printf("ret1:%d\n", ret);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
printf("ret2:%d\n", ret);
	ocl->context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
printf("ret3:%d\n", ret);
	ocl->command_queue = clCreateCommandQueue(ocl->context, device_id, 0, &ret);
printf("ret4:%d\n", ret);
	ocl->program = clCreateProgramWithSource(ocl->context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);	
printf("ret5:%d\n", ret);
	ret = clBuildProgram(ocl->program, 1, &device_id, NULL, NULL, NULL);
printf("ret6:%d\n", ret);
	(ocl->kernel)[0] = clCreateKernel(ocl->program, "test_image", &ret);
printf("ret7:%d\n", ret);
	(ocl->kernel)[1] = clCreateKernel(ocl->program, "define_ray_dir", &ret);
printf("ret8:%d\n", ret);
	free(source_str);
	return (ocl);
}





/*
void		actual_ocl_data(t_mem_ocl *mem)
{	
	(void)mem;
}

*/
int			destroy_ocl(t_ocl **ocl)
{
	int		i;
	cl_int	ret;

	if (!ocl || !*ocl)
		return (0);
	ret = clFlush((*ocl)->command_queue);	
	ret = clFinish((*ocl)->command_queue);
	ret = clReleaseProgram((*ocl)->program);

	i = 0;
	while (i > NB_KERNEL)
	{
		ret = clReleaseKernel(((*ocl)->kernel)[i]);
		i++;
	}

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
	ret = clReleaseMemObject((*mem)->ocl_time);
	ret = clReleaseMemObject((*mem)->ocl_data);
	*mem = NULL;
	return (1);
}
