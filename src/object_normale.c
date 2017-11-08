/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:16:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:17:19 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
