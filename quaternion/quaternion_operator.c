/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:27:58 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 17:28:55 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_quater	quaternion_scalar(t_quater q, double k)
{
	q.s = q.s * k;
	q.v.x = q.v.x * k;
	q.v.y = q.v.y * k;
	q.v.z = q.v.z * k;
	return (q);
}

double		quaternion_dot(t_quater q1, t_quater q2)
{
	return (q1.s * q2.s + q1.v.x * q2.v.x + q1.v.y * q2.v.y + q1.v.z * q2.v.z);
}

t_quater	quaternion_product(t_quater q1, t_quater q2)
{
	t_quater	r;

	r.s = q1.s * q2.s - vec3_dot(q1.v, q2.v);
	r.v.x = q1.s * q2.v.x + q2.s * q1.v.x + q1.v.y * q2.v.z - q2.v.y * q1.v.z;
	r.v.y = q1.s * q2.v.y + q2.s * q1.v.y + q1.v.z * q2.v.x - q2.v.z * q1.v.x;
	r.v.z = q1.s * q2.v.z + q2.s * q1.v.z + q1.v.x * q2.v.y - q2.v.x * q1.v.y;
	return (r);
}

t_quater	quaternion_add(t_quater q1, t_quater q2)
{
	t_quater	r;

	r.s = q1.s + q2.s;
	r.v.x = q1.v.x + q2.v.x;
	r.v.y = q1.v.y + q2.v.y;
	r.v.z = q1.v.z + q2.v.z;
	return (r);
}

t_quater	quaternion_sub(t_quater q1, t_quater q2)
{
	t_quater	r;

	r.s = q1.s - q2.s;
	r.v.x = q1.v.x - q2.v.x;
	r.v.y = q1.v.y - q2.v.y;
	r.v.z = q1.v.z - q2.v.z;
	return (r);
}
