/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:04:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/10 23:35:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

#include <math.h>
#include <stdio.h>
#include <string.h>

# define VDIM 3
//typedef double	t_vec;

typedef	union	u_axes
{
	double		comp[VDIM][VDIM];
	double		all[VDIM * VDIM];
}				t_axes;


/*
**	si la base a bien ete initialiser, axes[0-2] corespond a ux, uy et uz
*/

typedef	struct	s_basis
{
	double		pos[3];
	double		*axes[VDIM];
	double		ux[VDIM];
	double		uy[VDIM];
	double		uz[VDIM];
}				t_basis;

void			vec_add(double src_a[VDIM], double src_b[VDIM], double dst[VDIM]);
void			vec_copy(double src[VDIM], double dst[VDIM]);
void			vec_cross(double src_a[VDIM], double src_b[VDIM], double dst[VDIM]);
double			vec_dot(double src_a[VDIM], double src_b[VDIM]);
double			vec_get_norme(double vec[VDIM]);
void			vec_normalise(double src[VDIM], double dst[VDIM]);
void			vec_scalar_prod(double src[VDIM], double factor, double dst[VDIM]);
void			vec_set(double vec[VDIM], double a, double b, double c);				// mouahahaha c'est juste lalable ou VDIM = 3 cette fonction
void			vec_sub(double src_a[VDIM], double src_b[VDIM], double dst[VDIM]);

void			vec3_init(double *vec, double v0, double v1, double v2);		// must change name
//void			vec3_print(double vec[3]);									// must change name
//void			vec3_print_str(double vec[3], char *str);					// must change name

void			mat_set_id(double mat[VDIM][VDIM]);
void			mat_set_one_rot(double mat[VDIM][VDIM], int id1, int id2, double ang);
void			mat_set_all_rot(double mat[VDIM][VDIM], double ang[VDIM]);
void			mat_mult_mat(double src_l[VDIM][VDIM], double src_r[VDIM][VDIM], double dst[VDIM][VDIM]);
void			mat_mult_vec(double mat[VDIM][VDIM], double vec_src[VDIM], double vec_dst[VDIM]);

void			basis_describe(t_basis *b);
void			basis_init(t_basis *b);
void			basis_normalise(t_basis *b);
void			basis_orthonormalise(t_basis *b);
void			basis_reset(t_basis *b);
void			basis_rot_x(t_basis *b, double ang);
void			basis_rot_y(t_basis *b, double ang);
void			basis_rot_z(t_basis *b, double ang);
void			basis_set(t_basis *b, double ux[VDIM], double uy[VDIM], double uz[VDIM]);
void			basis_vec_w2b(t_basis *b, double src[VDIM], double dst[VDIM]); // vec: World -> Basis
void			basis_vec_b2w(t_basis *b, double src[VDIM], double dst[VDIM]); // vec: Basis -> World


#endif

/*
**	Alors il reste a faire:
**			- les fonction de dessin
**			- les fonction/gestion de hook souris
**				ca serrait un peu comme si on re faisait un systeme de fenetre youpi
**	
*/
