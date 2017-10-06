/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   q2y: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 19:45:00 q2y fjanoty           #+#    #+#             */
/*   Updated: 2017/10/06 20:46:03 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

#include <math.h>

typedef	struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef	struct	s_mat3
{
	t_vec3		ux;
	t_vec3		uy;
	t_vec3		uz;
}				t_mat3;

typedef	struct	s_quater
{
	float	s;
	t_vec3	v;
}				t_quater;

t_quater	quaternion_add(t_quater q1, t_quater q2);
t_quater	quaternion_sub(t_quater q1, t_quater q2);
t_quater	quaternion_scalar(t_quater q, float k);
float		quaternion_dot(t_quater q1, t_quater q2);
t_quater	quaternion_product(t_quater q1, t_quater q2);
t_quater	quaternion_conjugate(t_quater q);
float		quaternion_norme(t_quater q);
t_quater	quaternion_normalise(t_quater q);
t_vec3		quaternion_rot(t_vec3 pt, t_vec3 axe, float angle);

t_vec3		vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2);
float   	vec3_dot(t_vec3 v1, t_vec3 v2);
float   	vec3_norme(t_vec3 v);
t_vec3		vec3_normalise(t_vec3 v);
t_vec3		vec3_scalar(t_vec3 v, float factor);

t_vec3		vec3_cast(float vec[3]);
t_vec3		vec3_set(float x, float y, float z);


t_mat3	mat3_get_id();
t_vec3	mat3_mult_vec3(t_mat3 mat, t_vec3 vec);
t_mat3	mat3_mult_mat3(t_mat3 m1, t_mat3 m2);
t_mat3	mat3_rot_z(float ang);
t_mat3	mat3_rot_y(float ang);
t_mat3	mat3_rot_x(float ang);
t_mat3	mat3_rot_all(float ang_x, float ang_y, float ang_z);
#endif
