/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_prototype.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 11:06:03 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 11:28:43 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_PROTOTYPE_H
# define RTV1_PROTOTYPE_H

# include "rtv1_typedef.h"
# include "rtv1.h"
# include "quaternion.h"
# include "mlx_key.h"
# include "libft.h"
# include "rtv1_define.h"
# include "rtv1_prototype.h"
# include "rtv1_env.h"



/*
**	lst.c
*/

t_lst		*lst_create_node(void *ptr);
t_lst		*lst_create_node_copy(void *ptr, size_t size);
void		lst_add_front(t_lst **beg, t_lst *node);
void		lst_add_back(t_lst **beg, t_lst *node);
void		lst_destroy_one(t_lst **node);
void		lst_destroy_all(t_lst **beg);
void		lst_map(t_lst *beg, void (*f)(void *data));
void		lst_map_env(t_lst *beg, void (*f)(void *env, void *ptr), void *env);
void		lst_remove_node(t_lst **beg, t_lst *target);
void		lst_remove_node_if(t_lst **beg, int (*f)(t_lst*));
void		lst_remove_destroy_node_if(t_lst **beg, int (*f)(t_lst*));

/*
**	cam.c
*/

void		cam_init(t_cam *cam);
void		cam_init_draw_func(t_env *e);
void		cam_reset(t_cam *cam);
void		cam_go_back(t_cam *cam, double dist);
void		cam_go_front(t_cam *cam, double dist);
void		cam_go_left(t_cam *cam, double dist);
void		cam_go_right(t_cam *cam, double dist);
void		cam_switch(t_mlx_win *w, t_item *item);
void		cam_turn_up(t_cam *cam, double ang);
void		cam_turn_down(t_cam *cam, double ang);
void		cam_turn_right(t_cam *cam, double ang);
void		cam_turn_left(t_cam *cam, double ang);
void		reset_zbuff(t_mlx_win *w);
void		find_collision(t_zbuff *zbuff, t_item *item, t_vec3 ray_dir);
void		color_scene(t_mlx_win *w, t_light *light, t_obj *obj);

/*
**	object.c
*/

void		obj_set_invrot(t_obj *obj, double rx, double ry, double rz);
t_vec3		obj_get_pos(t_vec3 ray_pos, t_vec3 ray_dir, double dist);
void		plan_init(t_obj *plan);
t_vec3		dist_all_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir);
t_vec3		dist_all_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir);
t_vec3		dist_all_plan(t_obj *plan, t_vec3 ray_pos, t_vec3 ray_dir);
t_vec3		dist_all_sphere(t_obj *sphere, t_vec3 ray_pos, t_vec3 ray_dir);
double		get_dist_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir);
double		get_dist_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir);
double		get_dist_plan(t_obj *plan, t_vec3 ray_pos, t_vec3 ray_dir);
double		get_dist_sphere(t_obj *sphere, t_vec3 ray_pos, t_vec3 ray_dir);
t_vec3		get_normal_cone(t_obj *cone, t_vec3 pos_impact);
t_vec3		get_normal_cylinder(t_obj *cylinder, t_vec3 pos_impact);
t_vec3		get_normal_plan(t_obj *plan, t_vec3 pos_impact);
t_vec3		get_normal_sphere(t_obj *sphere, t_vec3 pos_impact);

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

int			main_bcl(t_env *e);
int			mousse_motion(int x, int y, t_mlx_win *w);
int			mousse_release(int button, int x, int y, t_mlx_win *w);
int			mousse_press(int button, int x, int y, t_mlx_win *w);
int			key_release(int key_code, t_mlx_win *w);
int			key_press(int key_code, t_mlx_win *w);


/*
**	main.c
*/

t_env		*get_env(t_env *e);

/*
**	exit.c
*/

void		rtv1_exit(t_env *e);

/*
**	test.c
*/

void		test_cam_axes(t_cam *c);
void		test_basique(t_env *e);
void		rotation_test(void);

void		test_init_obj(t_obj *obj);
void		test_init_light(t_light *light, int nb_light);

/*
**	item.c
*/

void		cam_describe2(t_cam *cam);
void		item_destroy(t_item *it);
void		item_init(t_item *item, t_mlx_win *w, const char *str);

/*
**	get_file.c
*/

char		*file_get_str(const char *file_path, int *size);

/*
**	parse_rtv1.c
*/

int			item_obj_alloc(t_entities *node, t_item *item);
void		entities_destroy(t_entities *elem);
t_entities	*get_entities(char *file_str);
void		item_fill(t_entities *beg, t_item *item);

/*
**	debug.c
*/
void		test_ray(t_mlx_win *w, t_item *item, int i, int j);

/*
**	ray.c
*/

t_vec3		ray_reflect(t_vec3 ray_dir, t_vec3 normal);
void		launch_ray(t_mlx_win *w, t_item *item);

/*
**	ray_condition.c
*/

int			is_opposite_side(t_vec3 nrm1, t_vec3 nrm2, t_vec3 light_dir);
int			is_light_right_side(t_vec3 ray_dir, t_vec3 light_dir, t_vec3 nrm);
int			is_self_intersect(t_item *item, t_vec3 from, t_vec3 to, int self);
int			is_free_path(t_item *item, t_vec3 from, t_vec3 to, int self);
int			is_light(t_item *item, t_vec3 from, t_vec3 to, int self);

/*
**	post_processing.c
*/

void		pp_draw_light_flat(t_mlx_win *w, t_light *l, double r, t_vec3 col);
void		pp_draw_segment(t_mlx_win *w, t_vec3 from, t_vec3 to, t_vec3 color);

/*
**	segment.c
*/

t_seg		seg_set(t_vec3 from, t_vec3 to, t_vec3 c1, t_vec3 c2);
t_seg		*seg_create(t_vec3 from, t_vec3 to, t_vec3 c1, t_vec3 c2);
void		seg_add_obj_nrm(t_lst **beg, t_mlx_win *w, int x, int y);
void		seg_print(void *t_win_mlx, void *t_seg);

#endif
