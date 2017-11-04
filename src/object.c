/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:32:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 14:28:01 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

void	plan_init(t_obj *plan)
{
	plan->value = -vec3_dot(plan->dir, plan->pos);
}

double	get_min2(double a, double b)
{
	return ((a < b) ? a : b);
}

double	get_min3(double a, double b, double c)
{
	double	min;

	min = (a < b) ? a : b;
	min = (c < min) ? c : min;
	return (min);
}

double	solve_eq_2nd(double a, double b, double c)
{
	double	delta;
	double	r1;
	double	r2;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1);
	delta = sqrt(delta);
	r1 = (-delta - b) / (2 * a);
	r2 = (delta - b) / (2 * a);
	if (r1 < 0 && r2 < 0)
		return (-1);
	if (r1 < 0)
		return (r2);
	if (r2 < 0)
		return (r1);
	return ((r1 < r2) ? r1 : r2);
}

void	ray_adapt_pos_dir(t_vec3 *ray_dir, t_vec3 *ray_pos,
		t_vec3 obj_pos, t_mat3 rot_inv)
{
	*ray_pos = mat3_mult_vec3(rot_inv, vec3_sub(*ray_pos, obj_pos));
	*ray_dir = vec3_normalise(mat3_mult_vec3(rot_inv, *ray_dir));
}

void	obj_set_invrot(t_obj *obj, double rx, double ry, double rz)
{
	(void)rz;
	obj->rot_inv = mat3_rot_all(-rx, -ry, 0);
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

t_vec3	obj_get_pos(t_vec3 ray_pos, t_vec3 ray_dir, double dist)
{
	t_vec3	out;

	out = vec3_scalar(ray_dir, dist);
	out = vec3_add(out, ray_pos);
	return (out);
}

t_vec3	get_normal_plan(t_obj *plan, t_vec3 pos_impact)
{
	t_vec3	out;

	(void)pos_impact;
	out = vec3_scalar(plan->dir, 1);
	return (out);
}

t_vec3	get_normal_sphere(t_obj *sphere, t_vec3 pos_impact)
{
	t_vec3	out;

	out = vec3_sub(pos_impact, sphere->pos);
	out = vec3_normalise(out);
	out = vec3_scalar(out, -1);
	return (out);
}

t_vec3	get_normal_cylinder(t_obj *cylinder, t_vec3 pos_impact)
{
	t_vec3	out;
	double	coef;
	t_vec3	u;

	u = vec3_sub(pos_impact, cylinder->pos);
	coef = -vec3_dot(cylinder->dir, u) / vec3_dot(cylinder->dir, cylinder->dir);
	out = vec3_normalise(vec3_add(vec3_scalar(cylinder->dir, coef), u));
	return (out);
}

t_vec3	get_normal_cone(t_obj *cone, t_vec3 pos_impact)
{
	t_vec3	out;
	double	coef;
	t_vec3	u;

	u = vec3_sub(pos_impact, cone->pos);
	coef = -(vec3_dot(u, u)) / vec3_dot(cone->dir, u);
	out = vec3_normalise(vec3_add(vec3_scalar(cone->dir, coef), u));
	return (out);
}

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
