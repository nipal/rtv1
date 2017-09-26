/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:49:15 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/26 23:58:26 by fjanoty          ###   ########.fr       */
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

/*
**	|
**	v to be more readeble in get_dist_cone (object.c)
*/
# define RD0 ray_dir2[0]
# define RD1 ray_dir2[1]
# define RD2 ray_dir2[2]
# define RP0 cam->pos[0]
# define RP1 cam->pos[1]
# define RP2 cam->pos[2]


typedef	struct	s_env	t_env;

typedef	union	u_pix
{
	int			nb;
	char		comp[4];
}				t_pix;

typedef	struct	s_zbuff
{
	int			id;			// id de l'object
	float		dist;
	float		nrm[3];
	float		pos[3];
	//	normale surface


	//	rayon
	//	dir lumiere
}				t_zbuff;

typedef	struct	s_light
{
	float		pos[3];
	float		col[3];					// pour l'instant osef
	float		power;					// poura etre une condition d'arret si negatif
}				t_light;

typedef	struct	s_win_mlx
{
	t_env		*env;
	void		*img;
	void		*win;
	int			depth;
	int			endian;
	t_light		light[1];
	t_pix		*data;
	t_zbuff		*z_buff;
	t_basis		cam;
	char		*name;
	int			size_x;
	int			size_y;
	float		mouse[3];				//	position
	float		prev_mouse[3];			// prev pposition
}				t_mlx_win;

typedef	struct	s_obj
{
	int			type;
	float		col[3];					// pour l'instant comme on connais [0, 255] juste ca changera plus tard
	float		rot_inv[3][3];
	float		ang[3];	// on peut reconstruire ses transformation
	float		pos[3];
	float		dir[3];
	float		value;
}				t_obj;

typedef	struct	s_env
{
	void		*mlx;
	t_mlx_win	scene;
	float		(*obj_dist[4])(t_basis *cam, t_obj *o, float ray_dir[3]);
	void		(*obj_nrm[4])(t_obj *obj, float pos_impact[3], float result[3]);
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
void	find_collision(t_mlx_win *w, t_zbuff *zbuff, t_obj *obj, float ray_dir[3]);
void	fill_zbuff(t_mlx_win *w, t_basis *cam, t_obj *obj);
void	color_scene(t_mlx_win *w, t_light *light, t_obj *obj);

/*
**	object.c
*/

void	obj_set_invrot(t_obj *obj, float rx, float ry, float rz);
void	obj_set_pos(float ray_pos[3], float ray_dir[3], float dist, float result[3]);
void	plan_init(t_obj *plan);
float	get_dist_plan(t_basis *cam, t_obj *plan, float ray_dir[3]);
float	get_dist_sphere(t_basis *cam, t_obj *sphere, float ray_dir[3]);
float	get_dist_cone(t_basis *cam, t_obj *cone, float ray_dir[3]);
float	get_dist_cylinder(t_basis *cam, t_obj *cylinder, float ray_dir[3]);
void	set_normal_cone(t_obj *cone, float pos_impact[3], float result[3]);
void	set_normal_cylinder(t_obj *cylinder, float pos_impact[3], float result[3]);
void	set_normal_plan(t_obj *plan, float pos_impact[3], float result[3]);
void	set_normal_sphere(t_obj *sphere, float pos_impact[3], float result[3]);

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
**	init.c
*/

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
