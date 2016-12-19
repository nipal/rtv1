/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 05:46:36 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/19 10:05:19 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


t_mem_ocl	*init_mem_ocl(t_win *w, t_ocl *ocl)
{
	t_mem_ocl	*mem;
	cl_int		ret;
	int			size;

	if (!(mem = (t_mem_ocl*)ft_memalloc(sizeof(t_mem_ocl))))
		return (NULL);
	size = w->size_x * w->size_y;
	mem->img_data = (int*)w->data;
	mem->ocl_time = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(int), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mem->ocl_data = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, size * sizeof(int), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mem->ocl_ray_dir = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, size * 4 * sizeof(float), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mem->ocl_cam = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, 4 * 4 * sizeof(float), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mem->ray_dir = malloc(sizeof(float) * 4 * w->size_x * w->size_y);
		
	mem->cam[0 * 4 + 0] = 0;
	mem->cam[0 * 4 + 1] = 0;
	mem->cam[0 * 4 + 2] = 0;
	mem->cam[0 * 4 + 3] = 0;

	mem->cam[1 * 4 + 0] = 1;
	mem->cam[1 * 4 + 1] = 0;
	mem->cam[1 * 4 + 2] = 0;
	mem->cam[1 * 4 + 3] = 0;

	mem->cam[2 * 4 + 0] = 0;
	mem->cam[2 * 4 + 1] = 1;
	mem->cam[2 * 4 + 2] = 0;
	mem->cam[2 * 4 + 3] = 0;

	mem->cam[3 * 4 + 0] = 0;
	mem->cam[3 * 4 + 1] = 0;
	mem->cam[3 * 4 + 2] = 1;
	mem->cam[3 * 4 + 3] = 0;

	mem->ocl_zbuffer_id = clCreateBuffer(ocl->context, CL_MEM_READ_ONLY, 2 * size * sizeof(float), NULL, &ret);

	ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 0, sizeof(cl_mem), (void *)&(mem->ocl_ray_dir));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 1, sizeof(cl_mem), (void *)&(mem->ocl_cam));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 2, sizeof(cl_mem), (void *)&(mem->ocl_zbuffer_id));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	
	ret = clSetKernelArg((ocl->kernel)[TEST_IMAGE], 0, sizeof(cl_mem), (void *)&(mem->ocl_time));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clSetKernelArg((ocl->kernel)[TEST_IMAGE], 1, sizeof(cl_mem), (void *)&(mem->ocl_data));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;




//	mem->cam = malloc(100);
	return (mem);
}


void	print_test(t_mem_ocl *mem, t_win *w)
{
	int	i;
	int	j;

	j = 0;
	while (j < w->size_y)
	{
		i = 0;
		printf("[%d]	->", j);
		while (i < w->size_x)
		{
			printf("{%.2f, %.2f, %.2f} "
				, mem->ray_dir[(i + j * SIZE_X) * 4 + 0]
				, mem->ray_dir[(i + j * SIZE_X) * 4 + 1]	
				, mem->ray_dir[(i + j * SIZE_X) * 4 + 2]);
			i++;
		}
		printf("\n");
		j++;
	}
	printf("------------------------------------------------------------------------------------------\n");
}


int		main_while_ocl(t_mem_ocl *mem, t_ocl *ocl, t_win *w)
{
	static	int count = 0;
	cl_int	ret;
	size_t	global_item_size;
	size_t	local_item_size;
	int		size;
	char	tmp[1000];


	global_item_size = w->size_x * w->size_y;
	size = global_item_size;
	local_item_size = 1;
	
//		tmp[0] = '\0';
//		ft_strcat(tmp, __FILE__);
//		ft_strcat(tmp, " func:");
//		ft_strcat(tmp, __func__);
//	//		
//		set_landmark(mem->cam, w->cam_angle, w->cam_pos);
//		ret = clEnqueueWriteBuffer(ocl->command_queue, mem->ocl_cam, CL_TRUE, 0, 4 * 4 * sizeof(float), mem->cam, 0, NULL, NULL);
//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	//	
//	//		ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 0, sizeof(cl_mem), (void *)&(mem->ocl_ray_dir));
//	//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	//		ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 1, sizeof(cl_mem), (void *)&(mem->ocl_cam));
//	//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	//		ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 2, sizeof(cl_mem), (void *)&(mem->ocl_zbuffer_id));
//	//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	//		
//		ret = clEnqueueNDRangeKernel(ocl->command_queue, ocl->kernel[INIT_FRAME], 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//		ret = clEnqueueReadBuffer(ocl->command_queue, mem->ocl_ray_dir, CL_TRUE, 0, 4 * size * sizeof(float), mem->ray_dir, 0, NULL, NULL);
//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	


//mlx_put_image_to_window(w->e->mlx, w->win, w->img, 0, 0);


//****************************	On fait juste la couleur bizard	 ****************************
	ret = clEnqueueWriteBuffer(ocl->command_queue, mem->ocl_time, CL_TRUE, 0, sizeof(int), &count, 0, NULL, NULL);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;

	ret = clEnqueueNDRangeKernel(ocl->command_queue, (ocl->kernel)[TEST_IMAGE], 1, NULL,&global_item_size, &local_item_size, 0, NULL, NULL);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clEnqueueReadBuffer(ocl->command_queue, mem->ocl_data, CL_TRUE, 0,size * sizeof(int), mem->img_data, 0, NULL, NULL);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mlx_put_image_to_window(w->e->mlx, w->win, w->img, 0, 0);
	(void)tmp;


///	print_test(mem, w);

//	ret = clFlush((ocl)->command_queue);	
//	ret = clFinish((ocl)->command_queue);
	count++;
	return (0);
}
