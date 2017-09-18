/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:49:15 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/18 22:52:34 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define SCENE_X		640
# define SCENE_Y 		480

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

#include <stdlib.h>
#include "vec_math.h"

typedef	struct	s_env	t_env;

typedef	union	u_pix
{
	int			nb;
	char		comp[4];
}				t_pix;

typedef	struct	s_zbuff
{
	int			id;
	float		dist;
}				t_zbuff;

typedef	struct	s_win_mlx
{
	t_env		*env;
	void		*img;
	void		*win;
	int			depth;
	int			endian;
	t_pix		*data;
	t_zbuff		*z_buff;
	char		*name;
	int			size_x;
	int			size_y;
	float		mouse[3];				//	position
	float		prev_mouse[3];			// prev pposition
}				t_mlx_win;

typedef	struct	s_obj
{
	int			type;
	float		ang[3];
	float		pos[3];
	float		dir[3];
	float		radius;
}				t_obj;

typedef	struct	s_env
{
	void		*mlx;
	t_mlx_win	scene;
	t_basis		cam;
	float		(*obj_dist[4])(t_basis *cam, t_obj *o, float ray_dir[3]);
}				t_env;

/*
**	object.c
*/

float	get_dist_plan(t_basis *cam, t_obj *plan, float ray_dir[3]);
float	get_dist_sphere(t_basis *cam, t_obj *sphere, float ray_dir[3]);
float	get_dist_cone(t_basis *cam, t_obj *cone, float ray_dir[3]);
float	get_dist_cylinder(t_basis *cam, t_obj *cylinder, float ray_dir[3]);

/*
**	mlx_win.c
*/

int			win_mlx_init(t_mlx_win *w, int size_x, int size_y, char *name);
void		init_win_event(t_mlx_win *w);
void		win_mlx_finish(t_mlx_win *w);
void		mlx_start(t_env *e);


/*
**	event.c
*/

int		main_bcl(t_env *e);
int		mousse_motion(int x, int y, t_mlx_win *w);
int		mousse_release(int button, int x, int y, t_mlx_win *w);
int		mousse_press(int button, int x, int y, t_mlx_win *w);
int		key_release(int key_code, t_mlx_win *w);
int		key_press(int key_code, t_mlx_win *w);


/*
**	main.c
*/
t_env	*get_env();

/*
**	exit.c
*/
void	rtv1_exit(t_env *e);

#endif
