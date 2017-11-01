/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:33:59 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 16:36:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = (v1.y * v2.z) - (v1.z * v2.y);
	v3.y = (v1.z * v2.x) - (v1.x * v2.z);
	v3.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (v3);
}

t_vec3	vec3_scalar(t_vec3 v, double factor)
{
	t_vec3	r;

	r.x = v.x * factor;
	r.y = v.y * factor;
	r.z = v.z * factor;
	return (r);
}

double	vec3_norme(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3	vec3_normalise(t_vec3 v)
{
	double	coef;

	coef = fabs(vec3_norme(v));
	coef = (coef < 0.0000000001) ? 0 : 1 / coef;
	return (vec3_scalar(v, coef));
}
