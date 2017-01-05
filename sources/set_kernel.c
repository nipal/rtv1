/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_kernel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 03:58:11 by fjanoty           #+#    #+#             */
/*   Updated: 2017/01/05 03:50:51 by fjanoty          ###   ########.fr       */
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
	char		*names_kernel[NB_KERNEL];
	int			nb_kernel;
	char		*name_file;
	char		*source_file;
	cl_context	context;
}				t_kernel_param;


typedef	struct	s_kp_init
{
	char		*ker_names[NB_KERNEL];
	int			ker_nb;
	char		*src_name;
	char		*file_str;
	size_t		source_size;
	cl_context	context;
}				t_kp_init;

//	on initialise les nom de kernel
int	set_ker_names(t_kp_init *param, char **ker_names)
{
	int	i;

	i = 0;
	while (i < NB_KERNEL && ker_names[i])
	{
		param->ker_names[i] = ker_names[i];
		i++;
	}
	param->nb_kernel = i;
	return (1);
}


int	init_param(t_kp_init *param, cl_context context, char *src_name, char **ker_names)
{
	if (!param || !src_name, || !ker_names, || !*ker_names)
		return (0);
	param->context = context;
	param->src_name = src_name;
	set_ker_names(param, ker_names);
	if (!(param->source_str = read_file(src_name, &(param->source_size))))
		return (0);;
	return (1);
}





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



/*
**	On assemble tout les parmetre pour cree un nouveau PROGRAM et des nouveau KERNEL
**	on fait aussi la fonction pour les detruire, ou on ne fonction que par copy.
**	l'aventage des pointeur c'est que l'objet de retour transporte en l'ui l'information
**	du bon deroulement de l'iformation. On pourrai aussi dire que l'a notion de pointeur n'est
**	qu'une notion d'index. c'est a dire que on pourais un peu reconstruire la notion de pointeur juste
**	en manipulant des index. Ca serra probablement complex de reproduire le fonctionement des pointeur sur fonction
**	En tout cas il faudrait represente un genre d'arbre des relation pour un peu joue avec sertain mecanime
**	pour changer certaine maniere d'execution mais en ayant un peu optimiser le fonctionement.
*/

/* on a bedoin de   */
t_kernel_param	*get_source_info()
{
}

int				destroy_source_info()
{


}

{
	char		(*names_kernel)[NB_KERNEL];
	int			nb_kernel;
	char		*name_file;
	char		*source_file;
	cl_context	context;
}

int	reset_ocl_source(t_init_ocl_param *info, t_ocl *ocl)
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
	program = clCreateProgramWithSource(ocl->context, 1, (const char **)&param.source_str, (const size_t *)&param.source_size, ret);	
//	(ret[0] < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clBuildProgram(program, 1, &info->device_id, NULL, NULL, NULL);
//	(ret[1] < 0) ? print_ocl_error(ret + 1, __LINE__ - 1, __FILE__) : 0;
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
