/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:33:02 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 16:35:01 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vec3	vec3_add_scalar(t_vec3 v, double nb)
{
	v.x += nb;
	v.y += nb;
	v.z += nb;
	return (v);
}

t_vec3	vec3_add3(t_vec3 v1, t_vec3 v2, t_vec3 v3)
{
	t_vec3	v;

	v.x = v1.x + v2.x + v3.x;
	v.y = v1.y + v2.y + v3.y;
	v.z = v1.z + v2.z + v3.z;
	return (v);
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}
