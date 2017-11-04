/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:01:06 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 14:03:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TMP_H
# define TMP_H

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
int						mlx_win_is_inside(t_mlx_win *w, int x, int y);
int						mlx_win_init(t_mlx_win *w, int x, int y, char *name);
void					init_win_event(t_mlx_win *w);
void					mlx_win_finish(t_mlx_win *w);
void					mlx_start(t_env *e);
int						main_bcl(t_env *e);
int						mousse_motion(int x, int y, t_mlx_win *w);
int						mousse_release(int button, int x, int y, t_mlx_win *w);
int						mousse_press(int button, int x, int y, t_mlx_win *w);
int						key_release(int key_code, t_mlx_win *w);
int						key_press(int key_code, t_mlx_win *w);
t_env					*get_env(t_env *e);
void					rtv1_exit(t_env *e);
void					test_cam_axes(t_cam *c);
void					test_basique(t_env *e);
void					rotation_test(void);
void					test_init_obj(t_obj *obj);
void					test_init_light(t_light *light, int nb_light);
void					cam_describe2(t_cam *cam);
void					item_destroy(t_item *it);
void					item_init(t_item *item, t_mlx_win *w, const char *str);
char					*file_get_str(const char *file_path, int *size);
int						item_obj_alloc(t_entities *node, t_item *item);
void					entities_destroy(t_entities *elem);
t_entities				*get_entities(char *file_str);
void					item_fill(t_entities *beg, t_item *item);
void					test_ray(t_mlx_win *w, t_item *item, int i, int j);
t_vec3					ray_reflect(t_vec3 ray_dir, t_vec3 normal);
void					launch_ray(t_mlx_win *w, t_item *item);
int						is_opposite_side(t_vec3 n1, t_vec3 n2, t_vec3 l_dir);
int						is_light_right_side(t_vec3 r, t_vec3 l, t_vec3 n);
int						is_self_intersect(t_item *i, t_vec3 f, t_vec3 t, int s);
int						is_free_path(t_item *it, t_vec3 f, t_vec3 to, int s);
int						is_light(t_item *item, t_vec3 from, t_vec3 to, int s);
void					pp_draw_light_flat(t_mlx_win *w,
							t_light *l, double r, t_vec3 c);
void					pp_draw_segment(t_mlx_win *w, t_vec3 from,
							t_vec3 to, t_vec3 color);
t_seg					seg_set(t_vec3 from, t_vec3 to, t_vec3 c1, t_vec3 c2);
t_seg					*seg_create(t_vec3 f, t_vec3 t, t_vec3 c1, t_vec3 c2);
void					seg_add_obj_nrm(t_lst **beg, t_mlx_win *w, int x, int y);
void					seg_print(void *t_win_mlx, void *t_seg);

#endif
