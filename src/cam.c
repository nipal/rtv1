/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:30:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 09:24:19 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cam_switch(t_mlx_win *w, t_item *item)
{
	item->id_cam = (item->id_cam + 1) % item->nb_cam;
	w->cam = &item->all_cam[item->id_cam];
	item->cam = &item->all_cam[item->id_cam];
}

void	cam_go_front(t_cam *cam, double dist)
{
	cam->pos = vec3_add(cam->pos, vec3_scalar(cam->uz, dist));
}

void	cam_go_back(t_cam *cam, double dist)
{
	cam->pos = vec3_add(cam->pos, vec3_scalar(cam->uz, -dist));
}

void	cam_go_left(t_cam *cam, double dist)
{
	cam->pos = vec3_add(cam->pos, vec3_scalar(cam->ux, -dist));
}

void	cam_go_right(t_cam *cam, double dist)
{
	cam->pos = vec3_add(cam->pos, vec3_scalar(cam->ux, dist));
}

void	cam_turn_left(t_cam *cam, double ang)
{
	cam->ux = quaternion_rot(cam->ux, vec3_set(0, 1, 0), -ang);
	cam->uy = quaternion_rot(cam->uy, vec3_set(0, 1, 0), -ang);
	cam->uz = quaternion_rot(cam->uz, vec3_set(0, 1, 0), -ang);
}

void	cam_turn_right(t_cam *cam, double ang)
{
	cam->ux = quaternion_rot(cam->ux, vec3_set(0, 1, 0), ang);
	cam->uy = quaternion_rot(cam->uy, vec3_set(0, 1, 0), ang);
	cam->uz = quaternion_rot(cam->uz, vec3_set(0, 1, 0), ang);
}

void	cam_turn_down(t_cam *cam, double ang)
{
	cam->ux = quaternion_rot(cam->ux, cam->ux, -ang);
	cam->uy = quaternion_rot(cam->uy, cam->ux, -ang);
	cam->uz = quaternion_rot(cam->uz, cam->ux, -ang);
}

void	cam_turn_up(t_cam *cam, double ang)
{
	cam->ux = quaternion_rot(cam->ux, cam->ux, ang);
	cam->uy = quaternion_rot(cam->uy, cam->ux, ang);
	cam->uz = quaternion_rot(cam->uz, cam->ux, ang);
}


void	cam_reset(t_cam *cam)
{
	cam->pos = vec3_set(0, 0, 0);
	cam->ux = vec3_set(1, 0, 0);
	cam->uy = vec3_set(0, 1, 0);
	cam->uz = vec3_set(0, 0, 1);
}

void	cam_init(t_cam *cam)
{
	(void)cam;
	cam_init_draw_func(get_env(NULL));
}

void	cam_init_draw_func(t_env *e)
{
	e->obj_dist[0] = get_dist_plan;
	e->obj_dist[1] = get_dist_sphere;
	e->obj_dist[2] = get_dist_cylinder;
	e->obj_dist[3] = get_dist_cone;

	e->obj_nrm[0] = get_normal_plan;
	e->obj_nrm[1] = get_normal_sphere;
	e->obj_nrm[2] = get_normal_cylinder;
	e->obj_nrm[3] = get_normal_cone;
}

void	reset_zbuff(t_mlx_win *w)
{
	int	i;
	int	max;

	max = w->size_x * w->size_y;
	i = 0;
	while (i < max)
	{
		w->zbuff[i].id = -1;
		w->zbuff[i].dist = -1;
		i++;
	}
}
