/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rtv1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 07:46:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/14 12:29:23 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	run_rtv1()
{
	t_env	e;


	if (!(e.mlx = mlx_init()))
		return (-1);
	if (!(e.win_rt = window_init(&e, SIZE_X, SIZE_Y, "rtv1")))
		return (-2);
	if (!(e.ocl = init_kernel(SIZE_X, SIZE_Y, "src_cl/data_parallel.cl"))
		|| !(e.mem_ocl = init_mem_ocl(e.ocl, SIZE_X, SIZE_Y)))
		return (-3);
	mlx_loop_hook(e.mlx, main_bcl, &e);
	mlx_loop(e.mlx);
	mlx_do_sync(e.mlx);
	return (0);
}


int	main_bcl(t_env *e)
{
	(void)e;
	main_while_ocl(e->mem_ocl, e->ocl);
//	init_opencl(e, SIZE_X, SIZE_Y);
	return (0);
}
