/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 04:58:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:55:53 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include "quaternion.h"
# include "mlx_key.h"
# include "libft.h"

# define SCENE_X        400
# define SCENE_Y        200

# define BUFF_SIZE 1024

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

# define KEY_WORD_SIZE 16

# define OBJ_TYPE       0
# define ASSETS_COMP    1
# define CAM_COMP       2
# define LIGHT_COMP     3

# define TYPE_ASSET 0
# define TYPE_LIGHT 1
# define TYPE_CAM   2

# define PLAN       0
# define SPHERE     1
# define CYLINDER   2
# define CONE       3

# define RD0 ray_dir.x
# define RD1 ray_dir.y
# define RD2 ray_dir.z
# define RP0 ray_pos.x
# define RP1 ray_pos.y
# define RP2 ray_pos.z

# define DEG  (M_PI / 180)

# define ZERO_P 0.0000001
# define ZERO_N -0.0000001

typedef struct s_vec3	t_vec3;
typedef struct s_env	t_env;

typedef	struct			s_phong_coef
{
	double		amb;
	double		dif;
	double		spec;
}						t_coef_fong;

typedef struct			s_list
{
	int				size;
	char			*str;
	struct s_list	*next;
}						t_list;

typedef	struct			s_lst
{
	char				cpy;
	void				*ptr;
	struct s_lst		*next;
}						t_lst;

typedef	struct			s_seg
{
	t_vec3	from;
	t_vec3	to;
	t_vec3	c1;
	t_vec3	c2;
}						t_seg;

typedef	struct			s_index
{
	int			i;
	int			j;
}						t_index;

typedef	struct			s_val
{
	double	v1;
	double	v2;
}						t_val;

typedef	union			u_pix
{
	int					nb;
	unsigned	char	comp[4];
}						t_pix;

typedef	struct			s_zbuff
{
	int					id;
	double				dist;
	t_vec3				nrm;
	t_vec3				pos;
}						t_zbuff;

typedef	struct			s_light
{
	t_vec3				pos;
	t_vec3				col;
	double				power;
}						t_light;

typedef	struct			s_cam
{
	t_vec3				pos;
	t_vec3				ux;
	t_vec3				uy;
	t_vec3				uz;
}						t_cam;

typedef	struct			s_mlx_win
{
	t_env				*env;
	void				*img;
	void				*win;
	t_cam				*cam;
	int					depth;
	int					endian;
	t_pix				*data;
	t_zbuff				*zbuff;
	char				*name;
	int					size_x;
	int					size_y;
	double				ratio;
	t_vec3				mouse;
	t_vec3				prev_mouse;
	int					refresh;
}						t_mlx_win;

typedef	struct			s_obj
{
	int					type;
	t_vec3				col;
	t_mat3				rot_inv;
	t_vec3				pos;
	t_vec3				dir;
	double				value;
	double				pow_spec;
}						t_obj;

typedef	struct			s_item
{
	double		size_x;
	double		size_y;
	t_light		*light;
	t_obj		*obj;
	t_cam		*cam;
	t_cam		*all_cam;
	int			id_cam;
	int			nb_cam;
	int			nb_light;
	int			nb_obj;
	double		(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_dist_all[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_nrm[4])(t_obj *obj, t_vec3 pos_impact);
	t_lst		*all_segment;
}						t_item;

typedef	struct			s_entities
{
	int					type;
	int					sub_type;
	void				*entities;
	struct s_entities	*next;
}						t_entities;

struct					s_env
{
	void			*mlx;
	t_mlx_win		scene;
	double			(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3			(*obj_nrm[4])(t_obj *obj, t_vec3 pos_impact);
	t_item			item;
	long			frame;
	long			last_frame;
	int				visual_debug;
};

/*
**	lst.c
*/

t_lst					*lst_create_node(void *ptr);
t_lst					*lst_create_node_copy(void *ptr, size_t size);
void					lst_add_front(t_lst **beg, t_lst *node);
void					lst_add_back(t_lst **beg, t_lst *node);
void					lst_destroy_one(t_lst **node);
void					lst_destroy_all(t_lst **beg);
void					lst_map(t_lst *beg, void (*f)(void *data));
void					lst_map_env(t_lst *b, void (*f)(void *e, void *p)
							, void *e);
void					lst_remove_node(t_lst **beg, t_lst *target);
void					lst_remove_node_if(t_lst **beg, int (*f)(t_lst*));
void					lst_remove_destroy_node_if(t_lst **b, int (*f)(t_lst*));

/*
**	cam.c
*/

void					cam_init(t_cam *cam);
void					cam_init_draw_func(t_env *e);
void					cam_reset(t_cam *cam);
void					cam_go_back(t_cam *cam, double dist);
void					cam_go_front(t_cam *cam, double dist);
void					cam_go_left(t_cam *cam, double dist);
void					cam_go_right(t_cam *cam, double dist);
void					cam_switch(t_mlx_win *w, t_item *item);
void					cam_turn_up(t_cam *cam, double ang);
void					cam_turn_down(t_cam *cam, double ang);
void					cam_turn_right(t_cam *cam, double ang);
void					cam_turn_left(t_cam *cam, double ang);
void					reset_zbuff(t_mlx_win *w);
void					find_collision(t_zbuff *z, t_item *it, t_vec3 ray_dir);
void					color_scene(t_mlx_win *w, t_light *light, t_obj *obj);

/*
**	object.c
*/

double					solve_eq_2nd(double a, double b, double c);
void					ray_adapt_pos_dir(t_vec3 *ray_dir, t_vec3 *ray_pos,
						t_vec3 obj_pos, t_mat3 rot_inv);
void					obj_set_invrot(t_obj *o, double x, double y, double z);
t_vec3					obj_get_pos(t_vec3 r_pos, t_vec3 ray_dir, double dist);
void					plan_init(t_obj *plan);
t_vec3					dist_all_cone(t_obj *c, t_vec3 r_pos, t_vec3 r_dir);
t_vec3					dist_all_cylinder(t_obj *c, t_vec3 r_pos, t_vec3 r_dir);
t_vec3					dist_all_plan(t_obj *p, t_vec3 r_pos, t_vec3 r_dir);
t_vec3					dist_all_sphere(t_obj *s, t_vec3 r_pos, t_vec3 ray_di);
double					get_dist_cone(t_obj *cone, t_vec3 r_pos, t_vec3 r_dir);
double					get_dist_cylinder(t_obj *c, t_vec3 r_pos, t_vec3 r_dir);
double					get_dist_plan(t_obj *p, t_vec3 r_pos, t_vec3 r_dir);
double					get_dist_sphere(t_obj *s, t_vec3 r_pos, t_vec3 ray_dir);
t_vec3					get_normal_cone(t_obj *cone, t_vec3 pos_impact);
t_vec3					get_normal_cylinder(t_obj *cylinder, t_vec3 pos_impact);
t_vec3					get_normal_plan(t_obj *plan, t_vec3 pos_impact);
t_vec3					get_normal_sphere(t_obj *sphere, t_vec3 pos_impact);

/*
**	mlx_win.c
*/

int						mlx_win_is_inside(t_mlx_win *w, int x, int y);
int						mlx_win_init(t_mlx_win *w, int x, int y, char *name);
void					init_win_event(t_mlx_win *w);
void					mlx_win_finish(t_mlx_win *w);
void					mlx_start(t_env *e);

/*
**	event.c
*/

int						main_bcl(t_env *e);
int						mousse_motion(int x, int y, t_mlx_win *w);
int						mousse_release(int button, int x, int y, t_mlx_win *w);
int						mousse_press(int button, int x, int y, t_mlx_win *w);
int						key_release(int key_code, t_mlx_win *w);
int						key_press(int key_code, t_mlx_win *w);

/*
**	main.c
*/

t_env					*get_env(t_env *e);

/*
**	exit.c
*/

void					rtv1_exit(t_env *e);

/*
**	item.c
*/

void					cam_describe2(t_cam *cam);
void					item_destroy(t_item *it);
void					item_init(t_item *item, t_mlx_win *w, const char *str);

/*
**	get_file.c
*/

char					*file_get_str(const char *file_path, int *size);

/*
**	parse_is_function.c
*/

int						is_space(char c);
int						is_alphanum(char c);
int						is_parsing_finnished(char *str);
int						double_is_neg(double nb);

/*
**	parse_asset.c
*/

t_obj					*get_assets(char *str, int id, int *add_curs);

/*
**	parse_cam.c
*/

t_cam					*get_cam(char *str, int id, int *add_curs);

/*
**	parse_light.c
*/

t_light					*get_light(char *str, int id, int *add_curs);

/*
**	parse_entities_lst.c
*/

void					entities_push(t_entities **beg, t_entities *new_elem);
t_entities				*entities_create(void *data, int id);
void					entities_destroy(t_entities *elem);

/*
**	parse_item_fill.c
*/

void					item_fill(t_entities *beg, t_item *item);

/*
**	parse_key_word.c
*/

char					*get_tab(int tab_nb, int *siz);
int						find_id_from_name(char *word, int *add_curs, int tabid);

/*
**	parse_str_get.c
*/

double					str_get_double(const char *str, int *curs);
t_vec3					str_get_vec3(const char *str, int *curs, int *err);

/*
**	parse_str_move.c
*/

int						skip_withe_space(char *str);
int						skip_non_space(char *str);
int						find_char(const char *str, char target);
int						find_char_force(const char *str, char target);
int						get_word_size(char *str);

/*
**	parse_rtv1.c
*/

void					parse_error(int id, char *str);
void					color_range(t_vec3 *col);
void					obj_manage_rot(t_obj *obj);
void					remove_coment(char *str);
int						item_obj_alloc(t_entities *node, t_item *item);
void					entities_destroy(t_entities *elem);
t_entities				*get_entities(char *file_str);
void					item_fill(t_entities *beg, t_item *item);

/*
** 	ray_geo.c + ray_color.c + ray.c
*/

void					launch_ray(t_mlx_win *w, t_item *item);
void					find_collision(t_zbuff *zb, t_item *it, t_vec3 ray_dir);
t_vec3					ray_reflect(t_vec3 ray_dir, t_vec3 normal);

int						get_phong_color(t_item *item, t_zbuff *zbuff,
							t_vec3 ray_dir);

t_vec3					ray_reflect(t_vec3 ray_dir, t_vec3 normal);
void					launch_ray(t_mlx_win *w, t_item *item);

double					light_specular_coef(t_vec3 nrm, t_vec3 ray_dir
							, t_vec3 light_dir, double pow_spec);

double					light_difuse_coef(t_vec3 nrm,
							t_vec3 light_dir, double dist2);

/*
**	ray_condition.c
*/

int						is_opposite_side(t_vec3 n1, t_vec3 n2, t_vec3 l_dir);
int						is_light_right_side(t_vec3 r, t_vec3 l, t_vec3 n);
int						is_self_intersect(t_item *i, t_vec3 f, t_vec3 t, int s);
int						is_free_path(t_item *it, t_vec3 f, t_vec3 to, int s);

/*
**	post_processing.c
*/

void					pp_draw_light_flat(t_mlx_win *w,
							t_light *l, double r, t_vec3 c);
void					pp_draw_segment(t_mlx_win *w, t_vec3 from,
							t_vec3 to, t_vec3 color);

t_vec3					pp_screen_proj_coord(t_mlx_win *w, t_vec3 vec);
void					pp_put_pix(t_mlx_win *w, t_vec3 pos, t_vec3 col);
int						pp_get_light_color(double radius, double x,
							double y, t_vec3 col);

/*
**	segment.c
*/

t_seg					seg_set(t_vec3 from, t_vec3 to, t_vec3 c1, t_vec3 c2);
t_seg					*seg_create(t_vec3 f, t_vec3 t, t_vec3 c1, t_vec3 c2);
void					seg_add_obj_nrm(t_lst **beg, t_mlx_win *w,
									int x, int y);
void					seg_add_ray_light(t_lst **beg, t_mlx_win *w,
							int x, int y);
void					seg_print(void *win_mlx, void *seg);

#endif
