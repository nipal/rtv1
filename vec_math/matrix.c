/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:13:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/21 14:27:26 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"


void	mat_set_id(float mat[VDIM][VDIM])
{
	int	i;
	int	j;

	j = 0;
	while (j < VDIM)
	{
		i = 0;
		while (i < VDIM)
		{
			mat[j][i] = (i == j);
			i++;
		}
		j++;
	}
}

// x: y, z
// y: z, x
// z: x, y

void	mat_set_one_rot(float mat[VDIM][VDIM], int id1, int id2, float ang)
{
	mat_set_id(mat);
	mat[id1][id1] = cos(ang);
	mat[id2][id2] = cos(ang);
	mat[id1][id2] = -sin(ang);
	mat[id2][id1] = sin(ang);
}

void	mat_set_all_rot(float mat[VDIM][VDIM], float ang[VDIM])
{
	float	rot_tmp[VDIM][VDIM];
	int		i;

	mat_set_id(mat);
	i = 0;
	while (i < VDIM)
	{
		mat_set_one_rot(rot_tmp, (i + 1) % 3, (i + 2) % 3, ang[i]);
		mat_mult_mat(rot_tmp, mat, mat);
		i++;
	}
}

void	mat_mult_mat(float src_l[VDIM][VDIM], float src_r[VDIM][VDIM], float dst[VDIM][VDIM])
{
	float	tmp[VDIM][VDIM];
	int		i;
	int		j;
	int		k;

	j = 0;
	while (j < VDIM)
	{
		i = 0;
		while (i < VDIM)
		{
			tmp[j][i] = 0;
			k = 0;
			while (k < VDIM)
			{
				tmp[j][i] += src_l[j][k] * src_r[k][i];
				k++;
			}
			i++;
		}
		j++;
	}
	memmove(dst, tmp, sizeof(tmp));
}

void	mat_mult_vec(float mat[VDIM][VDIM], float vec_src[VDIM], float vec_dst[VDIM])
{
	float	tmp[VDIM];
	int	i;
	int	j;

	j = 0;
	while (j < VDIM)
	{
		tmp[j] = 0;
		i = 0;
		while (i < VDIM)
		{
			tmp[j] += vec_src[i] * mat[j][i];
			i++;
		}
		j++;
	}
	memmove(vec_dst, tmp, sizeof(tmp));
}
