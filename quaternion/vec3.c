/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 20:35:13 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/09 06:39:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_vec3	vec3_cast(double vec[3])
{
	t_vec3	v;

	v.x = vec[0];
	v.y = vec[1];
	v.z = vec[2];
	return (v);
}

t_vec3	vec3_set(double x, double y, double z)
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
	double	coef;

	out.z = vec3_norme(in);
	coef = in.z / (sqrt(in.x * in.x + in.z * in.z));
	out.y = acos(coef) * (((in.x) > 0) ? 1 : -1);
	out.x = asin(-in.y);
	return (out);
}

t_vec3	vec3_spherique_cartesien(t_vec3 in)
{
	t_vec3	out;

	out.z = in.z * cos(in.x) * cos(in.y);
	out.x = in.z * cos(in.x) * sin(in.y);
	out.y = -in.z * sin(in.x);
	return (out);
}
