/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 20:35:13 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/24 22:01:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_vec3		vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vec3		vec3_add_scalar(t_vec3 v, double nb)
{
	v.x += nb;
	v.y += nb;
	v.z += nb;
	return (v);
}

t_vec3		vec3_add3(t_vec3 v1, t_vec3 v2, t_vec3 v3)
{
	t_vec3	v;

	v.x = v1.x + v2.x + v3.x;
	v.y = v1.y + v2.y + v3.y;
	v.z = v1.z + v2.z + v3.z;
	return (v);
}

t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

double   	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = (v1.y * v2.z) - (v1.z * v2.y);
	v3.y = (v1.z * v2.x) - (v1.x * v2.z);
	v3.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (v3);
}

double   	vec3_norme(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3		vec3_scalar(t_vec3 v, double factor)
{
	t_vec3	r;

	r.x = v.x * factor;
	r.y = v.y * factor;
	r.z = v.z * factor;
	return (r);
}

t_vec3		vec3_normalise(t_vec3 v)
{
	double	coef;

	coef = fabs(vec3_norme(v));
	coef = (coef < 0.0000000001) ? 0 : 1 / coef;
	return (vec3_scalar(v, coef));
}

t_vec3		vec3_cast(double vec[3])
{
	t_vec3	v;

	v.x = vec[0];
	v.y = vec[1];
	v.z = vec[2];
	return (v);
}

t_vec3		vec3_set(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}


/*
**	Attention ce ne sont pas vraiment des coordoner spherique dans le sens ou
**	les axes choisie ne sont pas les bon
**	il y a des erreur avec ang_x == -M_PI / 2... probablement 
**	il faut aussi faire attention a normalize... dailler si on ne voudrai
**	pas trop se faire chier on pourrait l'itiliser puisqu'il a ete fixe
*/

t_vec3	vec3_cartesien_spherique(t_vec3 in)
{
	t_vec3	out;
	double	coef;

	out.z = vec3_norme(in);
	coef = in.z / (sqrt(in.x * in.x + in.z * in.z));
	out.y = acos(coef) * (((in.x) > 0) ? 1 : -1);
	out.x = asin(-in.y);
	return (out);
}

t_vec3	vec3_spherique_cartesien(t_vec3 in)
{
	t_vec3	out;

	out.z = in.z * cos(in.x) * cos(in.y);
	out.x = in.z * cos(in.x) * sin(in.y);
	out.y = -in.z * sin(in.x);
	return (out);
}

void	vec3_print(t_vec3 vec)
{
	printf("x:%f	y:%f	z:%f\n", vec.x, vec.y, vec.z);
}

void	vec3_print_str(t_vec3 vec, char *str)
{
	printf("%sx:%f	y:%f	z:%f\n", str, vec.x, vec.y, vec.z);
}
