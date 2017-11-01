/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_condition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:52:41 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 15:03:58 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	On veux savoir si les deux normale sont du meme cote du plan normale a la direction de la lumiere
**	nrm1, nrm2, light_dir
**		ENFAIT...  on ne s'en sert plus c'etait pour eviter un eventuel artefacte mais plus besoin
*/
int	is_opposite_side(t_vec3 nrm1, t_vec3 nrm2, t_vec3 light_dir)
{
	int	condition;

	condition = (vec3_dot(nrm1, light_dir) * vec3_dot(nrm2, light_dir)) < 0;
	if (debug_ray)
	{
		printf("is_opposite_side:	%s\n", (condition) ? "YES" : "no");
	}
	return (condition);
}

//	si la lumiere et la vue sont du meme cote de la normal
int		is_light_right_side(t_vec3 ray_dir, t_vec3 light_dir, t_vec3 normal)
{
	int	condition;

	ray_dir = vec3_normalise(ray_dir);
	light_dir = vec3_normalise(light_dir);
	normal = vec3_normalise(normal);
	condition = !((vec3_dot(normal, ray_dir) * vec3_dot(normal, light_dir)) > 0);
//	condition = 1;
//	return (1);
	if (debug_ray)
		printf("is_light_right_side:	%s\n", condition ? "YES" : "NO");
	return (condition);
}

int		is_self_intersect(t_item *item, t_vec3 from, t_vec3 to, int self)
{
	int		condition, c1, c2;
	t_vec3	solus;
	t_vec3	(**obj_dist_all)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);
	t_obj	*obj;
	t_vec3	dir;
	t_vec3	pt1, pt2, nrm1, nrm2, nrm_now;
	double	dist;
	(void)pt1; (void)pt2;(void)nrm1; (void)nrm2;(void)nrm_now;
//	int	inter_s1, inter_s2;

//return (0);
	dist = vec3_norme((dir = vec3_sub(to, from)));
	dir =  vec3_normalise(dir);
	obj = item->obj + self;
	obj_dist_all = item->obj_dist_all;
	solus = obj_dist_all[obj->type](obj, from, dir);
	c1 = (solus.x > ZERO_P && solus.x < dist);
	c2 = (solus.y > ZERO_P && solus.y < dist);
	condition = c1 || c2;

//	condition = 0;

//	pt1 = obj_get_pos(from, dir, solus.x);
//	pt2 = obj_get_pos(from, dir, solus.y);
//	nrm1 = item->obj_nrm[obj->type](obj, pt1);
//	nrm2 = item->obj_nrm[obj->type](obj, pt2);
//	nrm_now = item->obj_nrm[obj->type](obj, from);
	if (debug_ray)
	{
		printf("self_instersect	%s\n", (condition) ? "YES": "NO ");	
		printf("	s1:%f	dist:%f	=> %s\n", solus.x, dist, (c1) ? "SHADOW" : "--");
		printf("	s2:%f	dist:%f	=> %s\n", solus.y, dist, (c2) ? "SHADOW" : "--");
//	printf("s1:%.25f	dist:%.25f	s1:%s 	dot_now:%.25f	dot_s1:%.25f\n", solus.x, dist, (solus.x > ZERO_P && solus.x < dist) ? "TRUE " : "false", vec3_dot(nrm_now, dir), vec3_dot(nrm1, dir));
//	printf("s2:%.25f	dist:%.25f	s2:%s 	dot_now:%.25f	dot_s2:%.25f\n", solus.y, dist, (solus.y > ZERO_P && solus.y < dist) ? "TRUE " : "false", vec3_dot(nrm_now, dir), vec3_dot(nrm2, dir));

	}
//	if (((solus.x > 0 && solus.x < dist))
//		|| ((solus.y > 0 && dist < dist)))
//	printf("s1:%.15f	dist:%.15f	s1:%s 	dot_now:%.15f	dot_s1:%.15f\n", solus.x, dist, (solus.x > 0 && solus.x < dist) ? "TRUE " : "false", vec3_dot(nrm_now, dir), vec3_dot(nrm1, dir));
//	printf("s2:%.15f	dist:%.15f	s2:%s 	dot_now:%.15f	dot_s2:%.15f\n", solus.y, dist, (solus.y > 0 && solus.y < dist) ? "TRUE " : "false", vec3_dot(nrm_now, dir), vec3_dot(nrm2, dir));
	return (condition);
}

// si on a pas calculer la distance (au carre), on met -1
int		is_free_path(t_item *item, t_vec3 from, t_vec3 to, int self)
{
	t_obj	*obj;
	int		i;
	double		(**obj_dist)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3	dir;
	t_val	dist;

	dir = vec3_sub(to, from);
	dist.v1 = vec3_dot(dir, dir);
	dist.v1 = sqrt(dist.v1);
	dir = vec3_normalise(dir);
	obj_dist = item->obj_dist;
	obj = item->obj;
	i = 0;
	while (i < item->nb_obj)
	{
		(void)self;
		if (i == self && ++i)
		{
			if (is_self_intersect(item, from, to, self))
				return (0);
			continue ;
		}
		dist.v2 = obj_dist[obj[i].type](obj + i, from, dir);
		if ((float)dist.v2 > 1 && dist.v2 < dist.v1)
			return (0);
		i++;
	}
	return (1);
}

int		is_light(t_item *item, t_vec3 from, t_vec3 to, int self)
{
	if (!is_free_path(item, from, to, self))
		return (0);
	return (1);
}
