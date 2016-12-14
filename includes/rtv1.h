/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 02:08:51 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/14 09:51:58 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

#include <mlx.h>
#include "libft.h"
#include "c_maths.h"

#include <stdio.h>	
#include <stdlib.h>
#include <OpenCL/opencl.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>	
#include <stdlib.h>

#include <OpenCL/opencl.h>






#define MAX_SOURCE_SIZE (0x100000)	



/*
 	ON va faire une structure keybord et mousse avec plein de truc cool
	(en mode interface a lib)
 */

# define SIZE_X 1024
# define SIZE_Y 768

/*
**	dans t_ocl on a juste les variable de base pour lancer un kernel
**	apres on aurras sois une structure par kernel sois un tableau sois un verra
*/

typedef	struct			s_mem_ocl
{
	cl_mem				Amobj;	
	cl_mem				Bmobj;	
	cl_mem				Cmobj;	
	float				*A;
	float				*B;
	float				*C;
}						t_mem_ocl;

typedef	struct			s_ocl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;

	cl_program			program;
	cl_kernel			kernel;	
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
}						t_ocl;

typedef	union	u_pix
{
	int			nb;
	char		comp[4];
}				t_pix;

typedef	struct	s_env	t_env;

typedef	struct	s_win
{
	void		*img;
	void		*win;
	int			size_line;
	int			depth;
	int			endian;
	t_pix		*data;
	t_env		*e;
	char		*name;
	int			size_x;
	int			size_y;
}				t_win;



struct			s_env
{
	void		*mlx;
	t_win		*win_rt;
};


/*
**	init_rtv1
*/
int	run_rtv1();
int	main_bcl(t_env *e);


/*
**	init_win
*/
t_win			*window_init(t_env *e, int size_x, int size_y, char *name);
int				ft_free(void **ptr);
int				window_destroy(t_win **w);

/*
**	init_opencl
*/
int	init_opencl(t_env *e, int size_x, int size_y);
#endif
