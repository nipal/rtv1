/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:13:38 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/07 13:58:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

void			vec_copy(double src[VDIM], double dst[VDIM])
{
	int		i;
	
	i = 0;
	while (i < VDIM)
	{
		dst[i] = src[i];
		i++;
	}
}

void	vec_add(double src_a[VDIM], double src_b[VDIM], double dst[VDIM])
{
	int		i;
	
	i = 0;
	while (i < VDIM)
	{
		dst[i] = src_a[i] + src_b[i];
		i++;
	}
}

void	vec_sub(double src_a[VDIM], double src_b[VDIM], double dst[VDIM])
{
	int		i;
	
	i = 0;
	while (i < VDIM)
	{
		dst[i] = src_a[i] - src_b[i];
		i++;
	}
}

void	vec_cross(double src_a[VDIM], double src_b[VDIM], double dst[VDIM])
{
	double	tmp[VDIM];
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

void	vec_scalar_prod(double src[VDIM], double fact, double dst[VDIM])
{
	int		i;

	i = 0;
	while (i < VDIM)
	{
		dst[i] = src[i] * fact;
		i++;
	}
}

void	vec_set(double vec[VDIM], double a, double b, double c)
{
	vec[0] = a;
	vec[1] = b;
	vec[2] = c;
}

double	vec_dot(double src_a[VDIM], double src_b[VDIM])
{
	double	res;
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

void	vec_normalise(double src[VDIM], double dst[VDIM])
{
	double	dist;
	(void)dst;

	if ((dist = sqrt(vec_dot(src, src))) == 0)
		printf("Error length_vec = 0\n");
	else
		vec_scalar_prod(src, 1 / dist, dst);
}

double	vec_get_norme(double vec[VDIM])
{
	return (sqrt(vec_dot(vec, vec)));
}

void	vec3_init(double *vec, double v0, double v1, double v2)
{
	vec[0] = v0;
	vec[1] = v1;
	vec[2] = v2;
}

void	vec3_print(double vec[3])
{
	double	norme;

	norme = vec_get_norme(vec);
	printf("vec:|{%f, %f, %f}| = %f\n", vec[0], vec[1], vec[2], norme);
}

void	vec3_print_str(double vec[3], char *str)
{
	double	norme;

	norme = vec_get_norme(vec);
	printf("%s :|{%f, %f, %f}| = %f\n", str, vec[0], vec[1], vec[2], norme);

}
