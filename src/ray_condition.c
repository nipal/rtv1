/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_condition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:52:41 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 05:08:16 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		is_opposite_side(t_vec3 nrm1, t_vec3 nrm2, t_vec3 light_dir)
{
	int	condition;

	condition = (vec3_dot(nrm1, light_dir) * vec3_dot(nrm2, light_dir)) < 0;
	return (condition);
}

int		is_light_right_side(t_vec3 ray_dir, t_vec3 light_dir, t_vec3 normal)
{
	ray_dir = vec3_normalise(ray_dir);
	light_dir = vec3_normalise(light_dir);
	normal = vec3_normalise(normal);
	return (!((vec3_dot(normal, ray_dir) * vec3_dot(normal, light_dir)) > 0));
}

int		is_self_intersect(t_item *item, t_vec3 from, t_vec3 to, int self)
{
	t_vec3	solus;
	t_vec3	(**obj_dist_all)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);
	t_obj	*obj;
	t_vec3	dir;
	double	dist;

	dir = vec3_sub(to, from);
	dist = vec3_norme(dir);
	dir = vec3_normalise(dir);
	obj = item->obj + self;
	obj_dist_all = item->obj_dist_all;
	solus = obj_dist_all[obj->type](obj, from, dir);
	return ((solus.x > ZERO_P && solus.x < dist)
			|| (solus.y > ZERO_P && solus.y < dist));
}

int		is_free_path(t_item *item, t_vec3 from, t_vec3 to, int self)
{
	t_obj		*obj;
	int			i;
	double		(**obj_dist)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		dir;
	t_val		dist;

	dir = vec3_sub(to, from);
	dist.v1 = sqrt(vec3_dot(dir, dir));
	dir = vec3_normalise(dir);
	obj_dist = item->obj_dist;
	obj = item->obj;
	i = -1;
	while (++i < item->nb_obj)
	{
		if (i == self && ++i)
		{
			if (is_self_intersect(item, from, to, self))
				return (0);
			continue ;
		}
		dist.v2 = obj_dist[obj[i].type](obj + i, from, dir);
		if ((float)dist.v2 > 0.000001 && dist.v2 < dist.v1)
			return (0);
	}
	return (1);
}
