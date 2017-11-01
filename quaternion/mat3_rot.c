/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:22:27 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 17:23:23 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

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
