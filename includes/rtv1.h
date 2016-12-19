/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 02:08:51 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/19 06:02:38 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define SPHERE 	0
# define PLAN 		1
# define CYLINDRE	2
# define CONE		3

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

# include "mlx.h"
# include "libft.h"
# include "c_maths.h"

# include <stdio.h>	
# include <stdlib.h>
# include <OpenCL/opencl.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>	
# include <stdlib.h>

# include <OpenCL/opencl.h>
# include <math.h>
# define MAX_SOURCE_SIZE (0xf0000)	

char* g_ocl_error[100];


/*
 	ON va faire une structure keybord et mousse avec plein de truc cool
	(en mode interface a lib)
 */

//	# define SIZE_X 1024
//	# define SIZE_Y 768
# define SIZE_X 5
# define SIZE_Y 5
# define NB_KERNEL 10

/*
**	dans t_ocl on a juste les variable de base pour lancer un kernel
**	apres on aurras sois une structure par kernel sois un tableau sois un verra
*/

typedef	struct	s_obj
{
	float		position[3];				
	float		direction[3];
	float		size;
	int			type;

}				t_obj;

typedef	struct			s_mem_ocl
{
	cl_mem				ocl_time;
	cl_mem				ocl_data;
	int					*img_data;
	float				cam[4 * 4];
	cl_mem				ocl_cam;
	cl_mem				ocl_ray_dir;
	float				*ray_dir;
}						t_mem_ocl;

typedef	struct			s_ocl
{
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel[NB_KERNEL];
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

	float		cam_ang_incr;
	float		cam_angle[4];
	float		cam_pos[4];
	float		mouse_pos[4];
	float		mouse_prev_pos[4];
	int			mode_cursor;
	int			cursor_on;
}				t_win;

typedef	struct	s_cam
{
	float		landmark[16];
}				t_cam;


struct			s_env
{
	void		*mlx;
	t_win		*win_rt;
	t_ocl		*ocl;
	t_mem_ocl	*mem_ocl;
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
void			init_win_event(t_win *w);

/*
**	init_opencl
*/
int	init_opencl(t_env *e, int size_x, int size_y);

t_ocl		*init_kernel(int size_x, int size_y, const char *name_file);
t_mem_ocl	*init_mem_ocl(t_win *w, t_ocl *ocl);
int			main_while_ocl(t_mem_ocl *mem, t_ocl *ocl, t_win *w);
void		actual_ocl_data(t_mem_ocl *mem);
int			destroy_ocl(t_ocl **ocl);
int			destroy_mem_ocl(t_mem_ocl **mem);

/*
**	event
*/

int		press_key(int key_code, t_win *w);
int		release_key(int key_code, t_win *w);
int		motion_cursor(int x, int y, t_win *w);
int		press_cursor(int button, int x, int y, t_win *w);
int		release_cursor(int button, int x, int y, t_win *w);

/*
**	exit
*/
int		ft_exit(t_env *e);

/*
**	hook
*/
int		main_while_ocl(t_mem_ocl *mem, t_ocl *ocl, t_win *w);
t_mem_ocl	*init_mem_ocl(t_win *w, t_ocl *ocl);

/*
**	math_vector
*/
void	mat_vector_prod(float *mat, float *vect);
void	set_vect_val(float *vect, float a, float b, float c);
void	set_identity_in(float *dest);
void	set_rot_mat4(float *mat, float angle, int id1, int id2);
void	mult_mat4_in(float *mat1, float *mat2, float *mat_in);
void	set_landmark(float *landmark, float *ang, float *pos);
void	print_mat4(float *mat);
void	print_vect4(float *vect);

/*
**	error_opencl
*/
void	init_ocl_error();
void	print_ocl_error(int err_cl, int nb, char *name);
//	void	print_ocl_error_test(int err_cl, int nb, char *name);
#endif
