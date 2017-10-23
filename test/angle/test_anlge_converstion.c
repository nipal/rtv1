/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_anlge_converstion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:04:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/17 23:48:52 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "quaternion.h"


void	print_vec3(t_vec3 vec, const char *str)
{
	printf("%sx:%f	y:%f	z:%f\n", str, vec.x, vec.y, vec.z);
}

t_vec3	vec3_cartesien_spherique_2(t_vec3 in)
{
	t_vec3	out;
	double	coef;

	out.z = vec3_norme(in);
	coef = in.z / (sqrt(in.x * in.x + in.z * in.z));
	out.y = acos(coef) * (((in.x) > 0) ? 1 : -1);
	out.x = asin(-in.y);
	return (out);
}

t_vec3	vec3_spherique_cartesien_2(t_vec3 in)
{
	t_vec3	out;
	out.z = in.z * cos(in.x) * cos(in.y);
	out.x = in.z * cos(in.x) * sin(in.y);
	out.y = -in.z * sin(in.x);
	return (out);
}

/*
**	entrer : deux angle et un vecteur
**	elle imprime la diff...
*/

// On veux tester si les angle que l'ona  appliquer sont les bon
// donc on les appliquer

int	ang_is_equal(double a, double b)
{
//	printf("a:%f	b:%f\n", a, b);
	if (a < 0)
		a += ((int)(-a / (2 * M_PI) + 1) * 2 * M_PI);
	if (b < 0)
		b += ((int)(-b / (2 * M_PI) + 1) * 2 * M_PI);
//	printf("	a:%f	b:%f\n", a, b);
	if (fabs(fmod(a, 2 * M_PI) - fmod(b, 2 * M_PI)) < 0.0000000001)
		return (1);
	return (0);
}

int	test_diff_rot(t_vec3 in, double angx, double angy)
{
	int	ok;
	t_vec3	ux_rot, u1, u2, u3, v1, diff;
	t_vec3	ux = vec3_set(1, 0, 0);
	t_vec3	uy = vec3_set(0, 1, 0);

	ok = 1;
	ux_rot = quaternion_rot(ux, uy, angy);
	v1 = quaternion_rot(quaternion_rot(in, uy, angy), ux_rot, angx);
//	v1 = quaternion_rot(quaternion_rot(v1, ux_rot, -angx), uy, -angy);

	u3 = vec3_spherique_cartesien_2(vec3_cartesien_spherique_2(v1));
	u2 = vec3_cartesien_spherique_2(v1);
	diff = vec3_sub(u3, v1);
	if (fabs(vec3_norme(diff)) > 0.0000000001 || 1)
	{
		vec3_print_str(diff, "err_diff:");
//		printf("nrm:%f\n", vec3_norme(diff));
		ok = 0;
	}
	printf("X:%.20f - %.20f = %.20f		Y:%.20f - %.20f = %.20f		X:%s Y:%s\n", angx, u2.x, (angx - u2.x),  angy, u2.y, (angy - u2.y), (!ang_is_equal(angx, u2.x) ? "--": "OK"), (!ang_is_equal(angy, u2.y) ? "--" : "OK"));
	if (!ang_is_equal(angx, u2.x) || !ang_is_equal(angy, u2.y))
		ok = 0;
	return (ok);
}



int	main()
{
	int		i, j;
	int		step_i, step_j;
	t_vec3	v;
	double	ax, ay;

	i = 0;
	j = 0;
	step_i = 5;
	step_j = 5;
	v = vec3_set(0, 0, 1);
	
/*
	printf("*********  TEST X *********\n");
	// test angx:i angy:0
	for (i = -90; i < 90; i += step_i)
	{
		ax = (double)i * M_PI / 180.0;
		test_diff_rot(v, ax, 0);
	}
// */

/*
	printf("\n\n\n\n*********  TEST Y *********\n");
	// test angx:0 angy:i
	for (i = 0; i < 360; i += step_i)
	{
		ay = (double)i * M_PI / 180.0;
		test_diff_rot(v, 0, ay);
	}
// */


//*
	for (j = 0; j < 360; j += step_j)
	{
		for (i = -89; i < 90; i += step_i)
		{
			ax = (double)i * M_PI / 180.0;
			ay = (double)j * M_PI / 180.0;
			test_diff_rot(v, ax, ay);
		}
	}
// */
	return (0);
}
