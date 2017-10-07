/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:13:22 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/07 13:58:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

void	basis_describe(t_basis *b)
{
	printf("pos:	{%f, %f, %f}\n\
			ux :	{%f, %f, %f}\n\
			uy :	{%f, %f, %f}\n\
			uz :	{%f, %f, %f}\n", b->pos[0], b->pos[1], b->pos[2],
									b->ux[0], b->ux[1], b->ux[2],
									b->uy[0], b->uy[1], b->uy[2],
									b->uz[0], b->uz[1], b->uz[2]);
}

void	basis_init(t_basis *b)
{
	b->axes[0] = b->ux;
	b->axes[1] = b->uy;
	b->axes[2] = b->uz;
}

void	basis_reset(t_basis *b)
{
	vec_set(b->pos, 0, 0, 0);
	vec_set(b->ux, 1, 0, 0);
	vec_set(b->uy, 0, 1, 0);
	vec_set(b->uz, 0, 0, 1);
	basis_init(b);
}

void	basis_set(t_basis *b, double ux[VDIM], double uy[VDIM], double uz[VDIM])
{
	memmove(b->ux, ux, sizeof(double) * 3);
	memmove(b->uy, uy, sizeof(double) * 3);
	memmove(b->uz, uz, sizeof(double) * 3);
}

void	basis_normalise(t_basis *b)
{
	vec_normalise(b->ux, b->ux);
	vec_normalise(b->uy, b->uy);
	vec_normalise(b->uz, b->uz);
}

/*
**	basis_orthonormalise
**	
**	normalent a la sortie on a une base ortho normer pafait
**		par contre il faut que (ux dot_prod uy) != 0 
**		si non il y aurra juste des normalisation
*/

void	basis_orthonormalise(t_basis *b)
{
	vec_cross(b->ux, b->uy, b->uz);
	vec_normalise(b->uz, b->uz);
	vec_cross(b->uz, b->ux, b->uy);
	vec_normalise(b->uy, b->uy);
	vec_normalise(b->ux, b->ux);
}

// vec: World -> Basis
void	basis_vec_w2b(t_basis *b, double src[VDIM], double dst[VDIM])
{
	double	diff[VDIM];
	double	tmp[VDIM];
	int		i;

	vec_sub(src, b->pos, diff);
	i = 0;
	while (i < VDIM)
	{
		tmp[i] = vec_dot(b->axes[i], diff);
		i++;
	}
	memmove(dst, tmp, sizeof(tmp));
}

// vec: Basis -> World
void	basis_vec_b2w(t_basis *b, double src[VDIM], double dst[VDIM])
{
	double	tmp[VDIM];
	double	result[VDIM];
	int		i;

	memmove(result, b->pos, sizeof(result));
	i = 0;
	while (i < VDIM)
	{
		vec_scalar_prod(b->axes[i], src[i], tmp);
		vec_add(result, tmp, result);
		i++;
	}
	memmove(dst, result, sizeof(result));
}


void	basis_rot_x(t_basis *b, double ang)
{
	double	rot[VDIM][VDIM];
	int		i;

	mat_set_one_rot(rot, 1, 2, ang); // autoure de X
	i = 0;
	while (i < VDIM)
	{
		mat_mult_vec(rot, b->axes[i], b->axes[i]);
		i++;
	}
}

void	basis_rot_y(t_basis *b, double ang)
{
	double	rot[VDIM][VDIM];
	int		i;

	mat_set_one_rot(rot, 2, 0, ang); // autoure de Y
	i = 0;
	while (i < VDIM)
	{
		mat_mult_vec(rot, b->axes[i], b->axes[i]);
		i++;
	}
}

void	basis_rot_z(t_basis *b, double ang)
{
	double	rot[VDIM][VDIM];
	int		i;

	mat_set_one_rot(rot, 0, 1, ang); // autoure de Z
	i = 0;
	while (i < VDIM)
	{
		mat_mult_vec(rot, b->axes[i], b->axes[i]);
		i++;
	}
}
