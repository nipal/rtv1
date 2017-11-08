/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:14:22 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:23:00 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ray_adapt_pos_dir(t_vec3 *ray_dir, t_vec3 *ray_pos,
		t_vec3 obj_pos, t_mat3 rot_inv)
{
	*ray_pos = mat3_mult_vec3(rot_inv, vec3_sub(*ray_pos, obj_pos));
	*ray_dir = vec3_normalise(mat3_mult_vec3(rot_inv, *ray_dir));
}

double	get_dist_plan(t_obj *plan, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	dist;

	dist = -(vec3_dot(plan->dir, ray_pos) + plan->value)
		/ (vec3_dot(plan->dir, ray_dir));
	return (dist);
}

double	get_dist_sphere(t_obj *sphere, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	dist;
	double	a;
	double	b;
	double	c;

	a = vec3_dot(ray_dir, ray_dir);
	b = 2 * (vec3_dot(ray_dir, ray_pos) - vec3_dot(ray_dir, sphere->pos));
	c = vec3_dot(ray_pos, ray_pos) + vec3_dot(sphere->pos, sphere->pos)
		- 2 * vec3_dot(ray_pos, sphere->pos) - sphere->value * sphere->value;
	dist = solve_eq_2nd(a, b, c);
	return (dist);
}

double	get_dist_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	ray_adapt_pos_dir(&ray_dir, &ray_pos, cylinder->pos, cylinder->rot_inv);
	a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y;
	b = 2 * (ray_dir.x * ray_pos.x + ray_dir.y * ray_pos.y);
	c = ray_pos.x * ray_pos.x + ray_pos.y * ray_pos.y
		- cylinder->value * cylinder->value;
	return (solve_eq_2nd(a, b, c));
}

double	get_dist_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	ray_adapt_pos_dir(&ray_dir, &ray_pos, cone->pos, cone->rot_inv);
	a = RD0 * RD0 + RD1 * RD1 - RD2 * RD2 * cone->value;
	b = 2 * (RD0 * RP0 + RD1 * RP1 - RD2 * RP2 * cone->value);
	c = RP0 * RP0 + RP1 * RP1 - RP2 * RP2 * cone->value;
	return (solve_eq_2nd(a, b, c));
}
