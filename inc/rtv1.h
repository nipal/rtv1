/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:49:15 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 06:21:29 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define SCENE_X		400
# define SCENE_Y 		200

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
**	use in parse_rtv1.c
*/

# define KEY_WORD_SIZE 16

# define OBJ_TYPE 		0
# define ASSETS_COMP	1
# define CAM_COMP		2
# define LIGHT_COMP		3

# define TYPE_ASSET	0
# define TYPE_LIGHT	1
# define TYPE_CAM	2

# define PLAN		0
# define SPHERE		1
# define CYLINDER	2
# define CONE		3


/*
**	|
**	v   to be more readeble in get_dist_cone (object.c)
*/
# define RD0 ray_dir.x
# define RD1 ray_dir.y
# define RD2 ray_dir.z
# define RP0 ray_pos.x
# define RP1 ray_pos.y
# define RP2 ray_pos.z

# define DEG  (M_PI / 180)

extern int debug_ray;
# define ZERO_P 0.0000001
# define ZERO_N -0.0000001

typedef	struct	s_lst	t_lst;
struct		s_lst
{
	char	cpy;
	void	*ptr;
	t_lst	*next;
};

typedef	struct	timeval t_time;

typedef	struct	s_seg
{
	t_vec3	from;
	t_vec3	to;
	t_vec3	c1;
	t_vec3	c2;		// dans l'enticipation de faire des degtrader avec des ligne
}				t_seg;

typedef	struct	s_index
{
	int			i;
	int			j;
	// may be k also
}				t_index;

typedef	struct	s_val
{
	double	v1;
	double	v2;
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
	double		dist;
	t_vec3		nrm;
	t_vec3		pos;
	//	dir lumiere		// est-ce qu'on la calcule deja une fois ??
}				t_zbuff;

typedef	struct	s_light
{
	t_vec3		pos;
	t_vec3		col;					// pour l'instant osef
	double		power;					// poura etre une condition d'arret si negatif
}				t_light;

typedef	struct	s_cam
{
	//	on pourrai aussi metre d'autre valeur comme la lageure de l'ecran. ou un pointeur vers elle...
	t_vec3		pos;
	t_vec3		ux;
	t_vec3		uy;
	t_vec3		uz;
}				t_cam;

typedef	struct	s_mlx_win
{
	t_env		*env;
	void		*img;
	void		*win;
	t_cam		*cam;		// c'est une adresse qui y est copier
	int			depth;
	int			endian;
	t_pix		*data;
	t_zbuff		*zbuff;
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
	double		value;
}				t_obj;

typedef	struct	s_item
{
	double		size_x;
	double		size_y;
	t_cam		*cam;					//		#CAM# on a une copie du pointeur ici qui est declarer dans t_mlx_win
	t_light		*light;
	t_obj		*obj;
	t_lst		*all_segment;	// ... 	on verra si c'est approprier
	int			nb_light;
	int			nb_obj;
	int			nb_cam;
	double		(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_dist_all[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_nrm[4])(t_obj *obj, t_vec3 pos_impact);
}				t_item;

typedef	struct	s_env
{
	void		*mlx;

	t_mlx_win	scene;
	double		(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_nrm[4])(t_obj *obj, t_vec3 pos_impact);
	t_item		item;
	long		frame;
	long		last_frame;
}				t_env;

typedef	struct	s_entities
{
	int					type;				// assets:0, light:1, cam:2
	int					sub_type;			// if assets:[0-4] else:0
	void				*entities;			//
	struct	s_entities	*next;
}				t_entities;


/////////// NEED TO TEST THE LST FUNCTION BECAUSE I DIDNT DO IT	\\\\\\\\\\\#
/*
**	lst.c
*/

t_lst	*lst_create_node(void *ptr);
t_lst	*lst_create_node_copy(void *ptr, size_t size);
void	lst_add_front(t_lst **beg, t_lst *node);
void	lst_add_back(t_lst **beg, t_lst *node);
void	lst_destroy_one(t_lst **node);
void	lst_destroy_all(t_lst **beg);
void	lst_map(t_lst *beg, void (*f)(void *data));
void	lst_map_env(t_lst *beg, void (*f)(void *env, void *ptr), void *env);
void	lst_remove_node(t_lst **beg, t_lst *target);
void	lst_remove_node_if(t_lst **beg, int (*f)(t_lst*));
void	lst_remove_destroy_node_if(t_lst **beg, int (*f)(t_lst*));

/*
**	cam.c
*/

void	cam_describe(t_cam *c);
void	cam_init(t_cam *cam);
void	cam_init_draw_func(t_env *e);
void	cam_reset(t_cam *cam);
void	cam_go_back(t_cam *cam, double dist);
void	cam_go_front(t_cam *cam, double dist);
void	cam_go_left(t_cam *cam, double dist);
void	cam_go_right(t_cam *cam, double dist);
void	cam_turn_up(t_cam *cam, double ang);
void	cam_turn_down(t_cam *cam, double ang);
void	cam_turn_right(t_cam *cam, double ang);
void	cam_turn_left(t_cam *cam, double ang);
void	reset_zbuff(t_mlx_win *w);
void	find_collision(t_zbuff *zbuff, t_item *item, t_vec3 ray_dir);
void	color_scene(t_mlx_win *w, t_light *light, t_obj *obj);

/*
**	object.c
*/

void	obj_set_invrot(t_obj *obj, double rx, double ry, double rz);
t_vec3	obj_get_pos(t_vec3 ray_pos, t_vec3 ray_dir, double dist);
void	plan_init(t_obj *plan);
t_vec3	dist_all_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir);
t_vec3	dist_all_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir);
t_vec3	dist_all_plan(t_obj *plan, t_vec3 ray_pos, t_vec3 ray_dir);
t_vec3	dist_all_sphere(t_obj *sphere, t_vec3 ray_pos, t_vec3 ray_dir);
double	get_dist_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir);
double	get_dist_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir);
double	get_dist_plan(t_obj *plan, t_vec3 ray_pos, t_vec3 ray_dir);
double	get_dist_sphere(t_obj *sphere, t_vec3 ray_pos, t_vec3 ray_dir);
t_vec3	get_normal_cone(t_obj *cone, t_vec3 pos_impact);
t_vec3	get_normal_cylinder(t_obj *cylinder, t_vec3 pos_impact);
t_vec3	get_normal_plan(t_obj *plan, t_vec3 pos_impact);
t_vec3	get_normal_sphere(t_obj *sphere, t_vec3 pos_impact);

/*
**	mlx_win.c
*/

int			mlx_win_is_inside(t_mlx_win *w, int x, int y);
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


void	test_cam_axes(t_cam *c);
void	test_basique(t_env *e);
void	rotation_test();

void	test_init_obj(t_obj *obj);
void	test_init_light(t_light *light, int nb_light);

/*
**	item.c
*/

void	obj_describe(t_obj *obj);
void	light_describe(t_light *light);
void	cam_describe2(t_cam *cam);
void	item_destroy(t_item *it);
void	item_init(t_item *item, t_mlx_win *w, const char *str);

/*
**	get_file.c
*/

char	*file_get_str(const char *file_path, int *size);

/*
**	parse_rtv1.c
*/

int		item_obj_alloc(t_entities *node, t_item *item);
void		entities_destroy(t_entities *elem);
t_entities	*get_entities(char *file_str);
void		item_fill(t_entities *beg, t_item *item);

//void	rtv1_parse_file(char *file_content, int file_size, t_item *item);

/*
**	debug.c
*/
void	test_ray(t_mlx_win *w, t_item *item, int i, int j);

/*
**	ray.c
*/

t_vec3	ray_reflect(t_vec3 ray_dir, t_vec3 normal);
void	launch_ray(t_mlx_win *w, t_item *item);

/*
**	ray_condition.c
*/

int		is_opposite_side(t_vec3 nrm1, t_vec3 nrm2, t_vec3 light_dir);
int		is_light_right_side(t_vec3 ray_dir, t_vec3 light_dir, t_vec3 normal);
int		is_self_intersect(t_item *item, t_vec3 from, t_vec3 to, int self);
int		is_free_path(t_item *item, t_vec3 from, t_vec3 to, int self);
int		is_light(t_item *item, t_vec3 from, t_vec3 to, int self);

/*
**	post_processing.c
*/

void	pp_draw_light_flat(t_mlx_win *w, t_light *l, double radius, t_vec3 col);
void	pp_draw_segment(t_mlx_win *w, t_vec3 from, t_vec3 to, t_vec3 color);

/*
**	segment.c
*/

t_seg	seg_set(t_vec3 from, t_vec3 to, t_vec3 c1, t_vec3 c2);
t_seg	*seg_create(t_vec3 from, t_vec3 to, t_vec3 c1, t_vec3 c2);
void	seg_add_obj_nrm(t_lst **beg, t_mlx_win *w, int x, int y);
void	seg_print(void *t_win_mlx, void *t_seg);
#endif
