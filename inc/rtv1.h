/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:49:15 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/06 20:40:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define SCENE_X		400
# define SCENE_Y 		400

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <mlx.h>
#include <stdlib.h>
#include "quaternion.h"
#include "mlx_key.h"
#include "vec_math.h"
#include "libft.h"

/*
**	|
**	v to be more readeble in get_dist_cone (object.c)
*/
# define RD0 ray_dir2.x
# define RD1 ray_dir2.y
# define RD2 ray_dir2.z
# define RP0 ray_pos.x
# define RP1 ray_pos.y
# define RP2 ray_pos.z

# define DEG  (M_PI / 180)

typedef	struct	timeval t_time;

typedef	struct	s_index
{
	int			i;
	int			j;
	// may be k also
}				t_index;

typedef	struct	s_val
{
	float	v1;
	float	v2;
}				t_val;

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
	t_vec3		nrm;
	t_vec3		pos;
	//	dir lumiere		// est-ce qu'on la calcule deja une fois ??
}				t_zbuff;

typedef	struct	s_light
{
	t_vec3		pos;
	t_vec3		col;					// pour l'instant osef
	float		power;					// poura etre une condition d'arret si negatif
}				t_light;

typedef	struct	s_mlx_win
{
	t_env		*env;
	void		*img;
	void		*win;
	t_basis		cam;
	int			depth;
	int			endian;
	t_pix		*data;
	t_zbuff		*z_buff;
	char		*name;
	int			size_x;
	int			size_y;
	t_vec3		mouse;				//	position
	t_vec3		prev_mouse;			// prev pposition
	int			refresh;
}				t_mlx_win;

typedef	struct	s_obj
{
	int			type;
	t_vec3		col;					// pour l'instant comme on connais [0, 255] juste ca changera plus tard
	t_mat3		rot_inv;
	t_vec3		ang;	// on peut reconstruire ses transformation
	t_vec3		pos;
	t_vec3		dir;
	float		value;
}				t_obj;

typedef	struct	s_item
{
	float		size_x;
	float		size_y;
	t_basis		*cam;
	t_light		*light;
	t_obj		*obj;
	int			nb_light;
	int			nb_obj;
	int			nb_cam;
	float		(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_nrm[4])(t_obj *obj, t_vec3 pos_impact);
}				t_item;

typedef	struct	s_env
{
	void		*mlx;

	t_mlx_win	scene;
	float		(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_nrm[4])(t_obj *obj, t_vec3 pos_impact);
	t_item		item;
	long		frame;
	long		last_frame;
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
void	launch_ray(t_mlx_win *w, t_item *item);
void	reset_zbuff(t_mlx_win *w);
void	find_collision(t_zbuff *zbuff, t_item *item, t_vec3 ray_dir);
void	color_scene(t_mlx_win *w, t_light *light, t_obj *obj);

/*
**	object.c
*/

void	obj_set_invrot(t_obj *obj, float rx, float ry, float rz);
t_vec3	obj_get_pos(t_vec3 ray_pos, t_vec3 ray_dir, float dist);
void	plan_init(t_obj *plan);
float	get_dist_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir);
float	get_dist_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir);
float	get_dist_plan(t_obj *plan, t_vec3 ray_pos, t_vec3 ray_dir);
float	get_dist_sphere(t_obj *sphere, t_vec3 ray_pos, t_vec3 ray_dir);
t_vec3	get_normal_cone(t_obj *cone, t_vec3 pos_impact);
t_vec3	get_normal_cylinder(t_obj *cylinder, t_vec3 pos_impact);
t_vec3	get_normal_plan(t_obj *plan, t_vec3 pos_impact);
t_vec3	get_normal_sphere(t_obj *sphere, t_vec3 pos_impact);

/*
**	mlx_win.c
*/

int			mlx_win_init(t_mlx_win *w, int size_x, int size_y, char *name);
void		init_win_event(t_mlx_win *w);
void		mlx_win_finish(t_mlx_win *w);
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

void	test_init_obj(t_obj *obj);
void	test_init_light(t_light *light, int nb_light);

/*
**	item.c
*/

void	init_cam(t_basis *cam);
void	item_destroy(t_item *it);
void	item_init(t_item *item, t_mlx_win *w, const char *str);

/*
**	get_file.c
*/

char	*file_str(const char *file_path, int *size);

/*
**	parseur.c
*/


void	rtv1_parse_file(char *file_content, int file_size, t_item *item);

#endif
