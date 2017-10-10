/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_anlge_converstion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:04:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/10 22:13:53 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../inc/quaternion.h"
#include <math.h>


void	print_vec3(t_vec3 vec, const char *str)
{
	printf("%sx:%f	y:%f	z:%f\n", str, vec.x, vec.y, vec.z);
}
/*
t_vec3	vec3_cartesien_spherique(t_vec3 in)
{
	t_vec3	out;
	t_vec3	u;

//	print_vec3(in, "-->");
	out.z = vec3_norme(in);
	in = vec3_normalise(in);
	u = vec3_normalise(vec3_set(in.x, 0, in.z));
	out.x = acos(vec3_dot(in, u));
	out.y = asin(u.x);
	return (out);
}

t_vec3	vec3_spherique_cartesien(t_vec3 in)
{
	t_vec3	out;
	t_vec3	ux;
	t_vec3	uy;

	uy = vec3_set(0, 1, 0);
	ux = vec3_set(1, 0, 0);
	out = vec3_set(0, 0, 1);
	out = quaternion_rot(out, uy, in.y);
	ux = quaternion_rot(ux, uy, in.y);
	out = quaternion_rot(out, ux, in.x);
	out = vec3_scalar(out, in.z);

//	out.x = in.z * cos(in.x) * cos(in.y);
//	out.y = in.z * cos(in.x) * sin(in.y);
//	out.z = in.z * cos(in.y);
	return (out);
}
*/
int	main()
{
	// L'idee c'est de calcucler deux angle en fonction du dot et du cross
	// puis de voir si il y a une difference quand on fait tourner une truc pour que oui
	t_vec3	v1 = vec3_normalise(vec3_set(0, 0, 4));
	t_vec3	v2 = vec3_set(0, 0, 1);
	t_vec3	v3;
	t_vec3	ux = vec3_set(1, 0, 0);
	t_vec3	ux_rot;
	t_vec3	uy = vec3_set(0, 1, 0);
	t_vec3	uz = vec3_set(0, 0, 1);
	t_vec3	u1, u2, u3, u4, u5, u6;

	double	angx, angy, a, b, c, d, e, f;

//	print_vec3();
	angx = 0.2737;
	angy = 0.1337;
	ux_rot = quaternion_rot(ux, uy, angy);
	v1 = quaternion_rot(v1, uy, angy);
	v1 = quaternion_rot(v1, ux_rot, angx);

	u3 = vec3_spherique_cartesien(vec3_cartesien_spherique(v1));
	u2 = vec3_cartesien_spherique(v1);

	vec3_print_str(u2, "u2:");
	vec3_print_str(u3, "u3:");
	vec3_print_str(v1, "v1:");
	
//	printf("ang_x:%f:%f	ang_y:%f:%f\n", angx, u2.x, angy, u2.y);
	

	/*
	v1 = vec3_normalise(v1);
	u1 = vec3_normalise(vec3_set(v1.x, 0, v1.z));

	print_vec3(v1, "v1:");
	print_vec3(u1, "u1:");
	a = acos(vec3_dot(u1, ux));
	b = asin(vec3_dot(u1, ux));	// angy
	c = acos(vec3_dot(u1, uy));
	d = asin(vec3_dot(u1, uy));
	e = acos(vec3_dot(v1, u1));	// angx
	f = asin(vec3_dot(v1, u1));
	printf("a:%f	b:%f	c:%f	d:%f	e:%f	f:%f\n", a, b, c, d, e, f);
	*/

//	printf("ang_x:%f	ang_y:%f\n", angx, angy);



	return (0);
}
