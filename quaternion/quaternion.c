/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 14:03:15 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 17:29:02 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_quater	quaternion_conjugate(t_quater q)
{
	q.v = vec3_scalar(q.v, -1);
	return (q);
}

double		quaternion_norme(t_quater q)
{
	return (sqrt(quaternion_dot(q, q)));
}

t_quater	quaternion_normalise(t_quater q)
{
	return (quaternion_scalar(q, 1.0 / quaternion_norme(q)));
}

t_vec3		quaternion_rot(t_vec3 pt, t_vec3 axe, double angle)
{
	t_quater	r;
	t_quater	q;

	angle *= 0.5;
	r.s = 0;
	r.v = pt;
	q.s = cos(angle);
	q.v = vec3_scalar(axe, sin(angle));
	r = quaternion_product(quaternion_product(q, r), quaternion_conjugate(q));
	return (r.v);
}
