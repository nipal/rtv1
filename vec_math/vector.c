/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:13:38 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/18 18:12:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

void	vec_add(float src_a[VDIM], float src_b[VDIM], float dst[VDIM])
{
	int		i;
	
	i = 0;
	while (i < VDIM)
	{
		dst[i] = src_a[i] + src_b[i];
		i++;
	}
}

void	vec_sub(float src_a[VDIM], float src_b[VDIM], float dst[VDIM])
{
	int		i;
	
	i = 0;
	while (i < VDIM)
	{
		dst[i] = src_a[i] - src_b[i];
		i++;
	}
}

void	vec_cross(float src_a[VDIM], float src_b[VDIM], float dst[VDIM])
{
	float	tmp[VDIM];
	int		i, id_1, id_2;

	i = 0;
	while (i < VDIM)
	{
		id_1 = (i + 1) % 3;
		id_2 = (i + 2) % 3;
		tmp[i] = src_a[id_1] * src_b[id_2] - src_a[id_2] * src_b[id_1];
		i++;
	}
	memmove(dst, tmp, sizeof(tmp));
}

void	vec_scalar_prod(float src[VDIM], float fact, float dst[VDIM])
{
	int		i;

	i = 0;
	while (i < VDIM)
	{
		dst[i] = src[i] * fact;
		i++;
	}
}

void	vec_set(float vec[VDIM], float a, float b, float c)
{
	vec[0] = a;
	vec[1] = b;
	vec[2] = c;
}

float	vec_dot(float src_a[VDIM], float src_b[VDIM])
{
	float	res;
	int		i;

	i = 0;
	res = 0;
	while (i < VDIM)
	{
		res += src_a[i] * src_b[i];
		i++;
	}
	return (res);
}

void	vec_normalise(float src[VDIM], float dst[VDIM])
{
	float	dist;
	(void)dst;

	if ((dist = sqrt(vec_dot(src, src))) == 0)
		printf("Error length_vec = 0\n");
	else
		vec_scalar_prod(src, 1 / dist, src);
}

float	vec_get_norme(float vec[VDIM])
{
	return (sqrt(vec_dot(vec, vec)));
}

void	vec3_init(float *vec, float v0, float v1, float v2)
{
	vec[0] = v0;
	vec[1] = v1;
	vec[2] = v2;
}
