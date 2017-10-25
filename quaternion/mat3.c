/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 19:03:55 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/25 15:38:17 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

void	mat3_print_str(t_mat3 m, char *str)
{
	printf("%s\n{", str);
	vec3_print_str(m.ux, "	ux:");
	vec3_print_str(m.uy, "	uy:");
	vec3_print_str(m.uz, "	uz:");
	printf("}");

}

t_mat3	mat3_get_id()
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

t_mat3	mat3_rot_z(double ang)
{
	t_mat3	rot;

	rot = mat3_get_id();
	rot.ux.x = cos(ang);
	rot.uy.y = cos(ang);
	rot.ux.y = -sin(ang);
	rot.uy.x = sin(ang);
	return (rot);
}

t_mat3	mat3_rot_y(double ang)
{
	t_mat3	rot;

	rot = mat3_get_id();
	rot.ux.x = cos(ang);
	rot.uz.z = cos(ang);
	rot.ux.z = sin(ang);
	rot.uz.x = -sin(ang);
	return (rot);
}

t_mat3	mat3_rot_x(double ang)
{
	t_mat3	rot;

	rot = mat3_get_id();
	rot.uy.y = cos(ang);
	rot.uz.z = cos(ang);
	rot.uy.z = -sin(ang);
	rot.uz.y = sin(ang);
	return (rot);
}

t_mat3	mat3_rot_all(double ang_x, double ang_y, double ang_z)
{
	t_mat3	rot_sum;

	rot_sum = mat3_mult_mat3(mat3_rot_x(ang_x), mat3_rot_y(ang_y));
	rot_sum = mat3_mult_mat3(rot_sum, mat3_rot_z(ang_z));
	return (rot_sum);
}
