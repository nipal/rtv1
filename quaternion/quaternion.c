/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.v.y                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   q2y: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 19:45:03 q2y fjanoty           #+#    #+#             */
/*   Updated: 2017/10/04 00:13:51 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

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

t_quater	quaternion_scalar(t_quater q, float k)
{
	q.s = q.s * k;
	q.v.x = q.v.x * k;
	q.v.y = q.v.y * k;
	q.v.z = q.v.z * k;
	return (q);
}

float	quaternion_dot(t_quater q1, t_quater q2)
{
	return(q1.s * q2.s + q1.v.x * q2.v.x + q1.v.y * q2.v.y + q1.v.z * q2.v.z);
}


//	q.s = Sa * Sa - dot(A, B)
//	q.v = Sa . B + Sb . A + A cross B
t_quater	quaternion_product(t_quater q1, t_quater q2)
{
	t_quater	r;

	r.s = q1.s * q2.s - vec3_dot(q1.v, q2.v);
	r.v.x = q1.s * q2.v.x + q2.s * q1.v.x + q1.v.y * q2.v.z + q2.v.y * q1.v.z;
	r.v.y = q1.s * q2.v.y + q2.s * q1.v.y + q1.v.z * q2.v.x + q2.v.z * q1.v.x;
	r.v.z = q1.s * q2.v.z + q2.s * q1.v.z + q1.v.x * q2.v.y + q2.v.x * q1.v.y;
	return (r);
}

//	q.s = Sa * Sa - dot(A, B)
//	q.v = Sa . B + Sb . A + A cross B
t_quater	quaternion_product2(t_quater q1, t_quater q2)
{
	t_quater	r;

	r.s = q1.s * q2.s - vec3_dot(q1.v, q2.v);
	r.v = vec3_add(vec3_add(vec3_scalar(q2.v, q1.s), vec3_scalar(q1.v, q2.s)), vec3_cross(q1.v, q2.v));
	return (r);
}


t_quater	quaternion_conjugate(t_quater q)
{
	q.v = vec3_scalar(q.v, -1);
	return (q);
}

float		quaternion_norme(t_quater q)
{
	return (sqrt(quaternion_dot(q, q)));
}

t_quater	quaternion_normalise(t_quater q)
{
	return (quaternion_scalar(q, 1.0 / quaternion_norme(q)));
}

// meintenant on veux faire des truc utile genre toutrne des baille
//


// p_rot = q p q_inv
t_vec3	quaternion_rot(t_vec3 pt, t_vec3 axe, float angle)
{
	t_quater	r;		// le pt qui devindra la rotation
	t_quater	q;		// le truc qui applique la rotation

	r.s = 0;
	r.v = pt;
	q.s = cos(angle);
	q.v = vec3_scalar(axe, sin(angle));
	r = quaternion_product(quaternion_product(q, r), quaternion_conjugate(q));
	return (r.v);
}


// To the next interpolation samere
