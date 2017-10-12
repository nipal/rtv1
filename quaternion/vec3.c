/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 20:35:13 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/12 17:42:36 by fjanoty          ###   ########.fr       */
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

t_vec3		vec3_add3(t_vec3 v1, t_vec3 v2, t_vec3 v3)
{
	t_vec3	v;

	v.x = v1.x + v2.x + v3.x;
	v.y = v1.y + v2.y + v3.y;
	v.z = v1.z + v2.z + v3.z;
	return (v);
}

t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

double   	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = (v1.y * v2.z) - (v1.z * v2.y);
	v3.y = (v1.z * v2.x) - (v1.x * v2.z);
	v3.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (v3);
}

double   	vec3_norme(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3		vec3_scalar(t_vec3 v, double factor)
{
	t_vec3	r;

	r.x = v.x * factor;
	r.y = v.y * factor;
	r.z = v.z * factor;
	return (r);
}

t_vec3		vec3_normalise(t_vec3 v)
{
	return (vec3_scalar(v, 1 / vec3_norme(v)));
}

t_vec3		vec3_cast(double vec[3])
{
	t_vec3	v;

	v.x = vec[0];
	v.y = vec[1];
	v.z = vec[2];
	return (v);
}

t_vec3		vec3_set(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec3_cartesien_spherique(t_vec3 in)
{
	t_vec3	out;
	t_vec3	u;

	out.z = vec3_norme(in);
	in = vec3_normalise(in);
	u = vec3_normalise(vec3_set(in.x, 0, in.z));
	out.x = acos(vec3_dot(in, u));
	out.y = asin(u.x);
	return (out);
}

t_vec3	vec3_spherique_cartesien(t_vec3 in)
{
	t_vec3	out;
	t_vec3	ux;
	t_vec3	uy;

	uy = vec3_set(0, 1, 0);
	ux = vec3_set(1, 0, 0);
	out = vec3_set(0, 0, 1);
	out = quaternion_rot(out, uy, in.y);
	ux = quaternion_rot(ux, uy, in.y);
	out = quaternion_rot(out, ux, in.x);
	out = vec3_scalar(out, in.z);
	return (out);
}

void	vec3_print(t_vec3 vec)
{
	printf("x:%f	y:%f	z:%f\n", vec.x, vec.y, vec.z);
}

void	vec3_print_str(t_vec3 vec, char *str)
{
	printf("%sx:%f	y:%f	z:%f\n", str, vec.x, vec.y, vec.z);
}
