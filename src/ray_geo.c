/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_geo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:44:28 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:52:55 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_find_collision(double *dst, int *best_id, double *best_dist)
{
	*dst = -1;
	*best_id = -1;
	*best_dist = -1;
}

void	find_collision(t_zbuff *zb, t_item *it, t_vec3 ray_dir)
{
	int		i;
	double	dst;
	double	best_dist;
	int		best_id;
	double	(**obj_dist)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);

	init_find_collision(&dst, &best_id, &best_dist);
	obj_dist = it->obj_dist;
	i = 0;
	while (i < it->nb_obj)
	{
		dst = obj_dist[it->obj[i].type](it->obj + i, it->cam->pos, ray_dir);
		if (dst > 0 && ((dst < best_dist && best_dist >= 0) || best_dist < 0))
		{
			best_dist = dst;
			best_id = i;
		}
		i++;
	}
	zb->id = best_id;
	zb->dist = best_dist;
	if (best_id < 0)
		return ;
	zb->pos = obj_get_pos(it->cam->pos, ray_dir, best_dist);
	zb->nrm = it->obj_nrm[it->obj[best_id].type](it->obj + best_id, zb->pos);
}

t_vec3	ray_reflect(t_vec3 ray_dir, t_vec3 normal)
{
	t_vec3	reflect;

	reflect = vec3_add(ray_dir, vec3_scalar(vec3_sub(vec3_scalar(
						normal, vec3_dot(ray_dir, normal)), ray_dir), 2));
	return (reflect);
}
