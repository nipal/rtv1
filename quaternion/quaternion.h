/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:28:34 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 17:24:23 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include <math.h>
# include <stdio.h>

typedef	struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef	struct	s_mat3
{
	t_vec3		ux;
	t_vec3		uy;
	t_vec3		uz;
}				t_mat3;

typedef	struct	s_quater
{
	double	s;
	t_vec3	v;
}				t_quater;

t_quater		quaternion_add(t_quater q1, t_quater q2);
t_quater		quaternion_sub(t_quater q1, t_quater q2);
t_quater		quaternion_scalar(t_quater q, double k);
double			quaternion_dot(t_quater q1, t_quater q2);
t_quater		quaternion_product(t_quater q1, t_quater q2);
t_quater		quaternion_conjugate(t_quater q);
double			quaternion_norme(t_quater q);
t_quater		quaternion_normalise(t_quater q);
t_vec3			quaternion_rot(t_vec3 pt, t_vec3 axe, double angle);

t_vec3			vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_add_scalar(t_vec3 v, double nb);
t_vec3			vec3_add3(t_vec3 v1, t_vec3 v2, t_vec3 v3);
t_vec3			vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_cross(t_vec3 v1, t_vec3 v2);
double			vec3_dot(t_vec3 v1, t_vec3 v2);
double			vec3_norme(t_vec3 v);
t_vec3			vec3_normalise(t_vec3 v);
t_vec3			vec3_scalar(t_vec3 v, double factor);
t_vec3			vec3_cartesien_spherique(t_vec3 in);
t_vec3			vec3_spherique_cartesien(t_vec3 in);
void			vec3_print(t_vec3 vec);
void			vec3_print_str(t_vec3 vec, char *str);

t_vec3			vec3_cast(double vec[3]);
t_vec3			vec3_set(double x, double y, double z);

t_mat3			mat3_get_id();
t_vec3			mat3_mult_vec3(t_mat3 mat, t_vec3 vec);
t_mat3			mat3_mult_mat3(t_mat3 m1, t_mat3 m2);
void			mat3_print_str(t_mat3 m, char *str);
t_mat3			mat3_rot_z(double ang);
t_mat3			mat3_rot_y(double ang);
t_mat3			mat3_rot_x(double ang);
t_mat3			mat3_rot_all(double ang_x, double ang_y, double ang_z);

#endif
