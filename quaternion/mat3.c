/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 19:03:55 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 17:23:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_mat3	mat3_get_id(void)
{
	t_mat3	mat;

	mat.ux = vec3_set(1, 0, 0);
	mat.uy = vec3_set(0, 1, 0);
	mat.uz = vec3_set(0, 0, 1);
	return (mat);
}

t_vec3	mat3_mult_vec3(t_mat3 mat, t_vec3 vec)
{
	t_vec3	v;

	v.x = vec3_dot(mat.ux, vec);
	v.y = vec3_dot(mat.uy, vec);
	v.z = vec3_dot(mat.uz, vec);
	return (v);
}

t_mat3	mat3_mult_mat3(t_mat3 m1, t_mat3 m2)
{
	t_mat3	m;
	t_vec3	vx;
	t_vec3	vy;
	t_vec3	vz;

	vx = vec3_set(m2.ux.x, m2.uy.x, m2.uz.x);
	vy = vec3_set(m2.ux.y, m2.uy.y, m2.uz.y);
	vz = vec3_set(m2.ux.z, m2.uy.z, m2.uz.z);
	m.ux.x = vec3_dot(m1.ux, vx);
	m.ux.y = vec3_dot(m1.ux, vy);
	m.ux.z = vec3_dot(m1.ux, vz);
	m.uy.x = vec3_dot(m1.uy, vx);
	m.uy.y = vec3_dot(m1.uy, vy);
	m.uy.z = vec3_dot(m1.uy, vz);
	m.uz.x = vec3_dot(m1.uz, vx);
	m.uz.y = vec3_dot(m1.uz, vy);
	m.uz.z = vec3_dot(m1.uz, vz);
	return (m);
}
