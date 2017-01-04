/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_kernel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 03:58:11 by fjanoty           #+#    #+#             */
/*   Updated: 2017/01/04 09:26:53 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Ici on va juste set les kernel
**	-on lit le fichier
**	-on on re cree program
**	-on re cree les kernel
**	-on definie les buffeur en argument
**	-on reset les comandequeu
*/


/*
**	char		*read_file(char *name);
*/

int	init	command_queue(int nb, )
{

}

typedef	struct	s_kernel_param
{
	char		*name_file;
	char		**names_kernel;
	int			nb_kernel;
}				t_kernel_param;

int	set_kernels(t_ocl *ocl, t_kernel_param *param, cl_kernel *new_kernel)
{
	int		i;
	cl_int	ret[2];

	if (!new_kernel || !param || !param->name_file || !param->names_kernel
			|| !(*(param->names_kernel)) || (param->nb_kernel <= 0))
		return (0);
	i = 0;
	while (i < param->nb_kernel && param->names_kernel[i])
	{
		new_kernel[i] = clCreateKernel(ocl->program, param->names_kernel[i], ret);
		(ret[0] < 0) ? print_ocl_error(ret[0], __LINE__ - 1, __FILE__) : 0;


		ret[1] = clBuildProgram(ocl->program, 1, &device_id, NULL, NULL, NULL);
		(ret[1] < 0) ? print_ocl_error(ret[1], __LINE__, __FILE__) : 0;
		if (ret[0] < 0 || ret[1] < 0)
			return (0);
		i++;
	}
	return (1);
}

int	set_program_kernel(t_init_ocl_param *info, t_ocl *ocl)
{
	cl_program		new_program;
	cl_kernel		new_kernel[NB_KERNEL];
	cl_int			ret[2];
	t_kernel_param param;

	if (!info || !ocl)
		return (-2);
	ft_bzero(new_kernel, sizeof(new_kernel));
	if (!(param.source_str = read_file(name_file, &param.source_size)))
		return (-1);
	program = clCreateProgramWithSource(ocl->context, 1
	, (const char **)&param.source_str, (const size_t *)&param.source_size, ret);	
	(ret[0] < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clBuildProgram(program, 1, &info->device_id, NULL, NULL, NULL);
	(ret[1] < 0) ? print_ocl_error(ret + 1, __LINE__ - 1, __FILE__) : 0;
	if (set_kernels(ocl, &param, new_kernel) && ret[0] >= 0 && ret[1] >= 0)
	{
		ocl->kernel = kernel;
		ft_memmove(ocl->kernel, new_kernel, sizeof(new_kernel));
		return (1);
	}
	else
		return (-1);
}

//	On doit changer le programme et les kernel
