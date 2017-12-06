/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:22:06 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:28:56 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "mlx_key.h"
#include <stdio.h>

int		key_press(int key_code, t_mlx_win *w)
{
	double	ang;
	double	dist;

	ang = 5;
	dist = 1;
	(void)key_code;
	(key_code == KEY_ESC) ? rtv1_exit(w->env) : (void)w;
	(key_code == KEY_A) ? cam_turn_left(w->cam, ang * DEG) : (void)w;
	(key_code == KEY_D) ? cam_turn_right(w->cam, ang * DEG) : (void)w;
	(key_code == KEY_S) ? cam_turn_down(w->cam, ang * DEG) : (void)w;
	(key_code == KEY_W) ? cam_turn_up(w->cam, ang * DEG) : (void)w;
	(key_code == KEY_H) ? cam_go_left(w->cam, dist) : (void)w;
	(key_code == KEY_L) ? cam_go_right(w->cam, dist) : (void)w;
	(key_code == KEY_J) ? cam_go_back(w->cam, dist) : (void)w;
	(key_code == KEY_K) ? cam_go_front(w->cam, dist) : (void)w;
	(key_code == KEY_P) ? cam_describe2(w->cam) : (void)w;
	(key_code == KEY_TAB) ? cam_switch(w, &w->env->item) : (void)w;
	(key_code == KEY_V) ? w->env->visual_debug++ : (void)w;
	w->refresh = 1;
	return (0);
}

int		mousse_press(int button, int x, int y, t_mlx_win *w)
{
	(void)w;
	if (button == BUTTON_LEFT)
	{
		if (w->env->visual_debug % 2)
			seg_add_obj_nrm(&w->env->item.all_segment, w, x, y);
		w->refresh = 1;
	}
	if (button == BUTTON_RIGHT)
	{
		if (w->env->visual_debug % 2)
			seg_add_ray_light(&w->env->item.all_segment, w, x, y);
		w->refresh = 1;
	}
	return (0);
}

void	print_all_segement(t_env *e)
{
	lst_map_env(e->item.all_segment, seg_print, &e->scene);
}

void	post_processing(t_env *e)
{
	t_mlx_win	*w;
	t_item		*item;
	int			i;

	w = &e->scene;
	item = &e->item;
	i = 0;
	while (i < item->nb_light)
	{
		pp_draw_light_flat(w, &item->light[i], 0.1, item->light[i].col);
		i++;
	}
	print_all_segement(e);
}

int		main_bcl(t_env *e)
{
	(void)e;
	if (e->scene.refresh)
	{
		e->scene.refresh = 0;
		launch_ray(&e->scene, &e->item);
		if (e->visual_debug % 2)
			post_processing(e);
		mlx_put_image_to_window(e->mlx, e->scene.win, e->scene.img, 0, 0);
	}
	return (0);
}
