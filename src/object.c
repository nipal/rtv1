/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:32:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:21:56 by fjanoty          ###   ########.fr       */
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

t_vec3	obj_get_pos(t_vec3 ray_pos, t_vec3 ray_dir, double dist)
{
	t_vec3	out;

	out = vec3_scalar(ray_dir, dist);
	out = vec3_add(out, ray_pos);
	return (out);
}
