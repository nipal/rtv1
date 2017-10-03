/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 20:35:13 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/03 20:55:18 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_vec3		vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

float   	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.y * v2.z - v2.z * v2.y;
	v3.y = v1.z * v2.x - v1.x * v2.z
	v3.z = v1.x * v2.y - v1.y * v2.x
	return (v3);
}

float   	vec3_norme(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3		vec3_scalar_prod(t_vec3 v, float factor)
{
	t_vec3	r;

	r.x = v.x * factor;
	r.y = v.y * factor;
	r.z = v.z * factor;
	return (v3);
}

t_vec3		vec3_normalise(t_vec3 v);
{
	return (vec3_scalar_prod(v, 1 / vec3_norme(v)));
}

