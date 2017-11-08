/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_dist_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:15:47 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:16:31 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	eq_2nd_get_all_solution(double a, double b, double c)
{
	double	delta;
	t_vec3	solus;

	solus = vec3_set(-1, -1, 0);
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (solus);
	delta = sqrt(delta);
	if ((solus.x = (-delta - b) / (2 * a)) >= 0)
		solus.z++;
	if ((solus.y = (delta - b) / (2 * a)) >= 0)
		solus.z++;
	return (solus);
}

t_vec3	dist_all_plan(t_obj *plan, t_vec3 ray_pos, t_vec3 ray_dir)
{
	(void)plan;
	(void)ray_pos;
	(void)ray_dir;
	return (vec3_set(-1, -1, 0));
}

t_vec3	dist_all_sphere(t_obj *sphere, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	a = vec3_dot(ray_dir, ray_dir);
	b = 2 * (vec3_dot(ray_dir, ray_pos) - vec3_dot(ray_dir, sphere->pos));
	c = vec3_dot(ray_pos, ray_pos) + vec3_dot(sphere->pos, sphere->pos)
		- 2 * vec3_dot(ray_pos, sphere->pos) - sphere->value * sphere->value;
	return (eq_2nd_get_all_solution(a, b, c));
}

t_vec3	dist_all_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	ray_adapt_pos_dir(&ray_dir, &ray_pos, cylinder->pos, cylinder->rot_inv);
	a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y;
	b = 2 * (ray_dir.x * ray_pos.x + ray_dir.y * ray_pos.y);
	c = ray_pos.x * ray_pos.x + ray_pos.y * ray_pos.y
		- cylinder->value * cylinder->value;
	return (eq_2nd_get_all_solution(a, b, c));
}

t_vec3	dist_all_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	ray_adapt_pos_dir(&ray_dir, &ray_pos, cone->pos, cone->rot_inv);
	a = RD0 * RD0 + RD1 * RD1 - RD2 * RD2 * cone->value;
	b = 2 * (RD0 * RP0 + RD1 * RP1 - RD2 * RP2 * cone->value);
	c = RP0 * RP0 + RP1 * RP1 - RP2 * RP2 * cone->value;
	return (eq_2nd_get_all_solution(a, b, c));
}
