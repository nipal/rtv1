/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:49:15 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/22 01:27:16 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define SCENE_X		640
# define SCENE_Y 		640

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

#include <mlx.h>
#include <stdlib.h>
#include "mlx_key.h"
#include "vec_math.h"
#include "libft.h"

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
	//	position
	//	normale surface


	//	rayon
	//	dir lumiere
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
**	cam.c
*/

void	cam_turn_up(t_basis *cam, float ang);
void	cam_turn_down(t_basis *cam, float ang);
void	cam_turn_right(t_basis *cam, float ang);
void	cam_turn_left(t_basis *cam, float ang);
void	cam_init_draw_func(t_env *e);
void	cam_rot(t_basis *cam, int x, int y);
void	reset_zbuff(t_mlx_win *w);
void	find_collision(t_env *e, t_zbuff *zbuff, t_obj *obj, float ray_dir[3]);
void	fill_zbuff(t_env *e, t_mlx_win *w, t_basis *cam, t_obj *obj);
void	color_scene(t_mlx_win *w, t_obj *obj);

/*
**	object.c
*/

void	plan_init(t_obj *plan);
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

/*
**	test.c
*/

void	test_basique(t_env *e);
void	rotation_test();

#endif
