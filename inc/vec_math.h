/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:04:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/03 20:29:34 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

#include <math.h>
#include <stdio.h>
#include <string.h>

# define VDIM 3
//typedef float	t_vec;

typedef	union	u_axes
{
	float		comp[VDIM][VDIM];
	float		all[VDIM * VDIM];
}				t_axes;


/*
**	si la base a bien ete initialiser, axes[0-2] corespond a ux, uy et uz
*/

typedef	struct	s_basis
{
	float		pos[3];
	float		*axes[VDIM];
	float		ux[VDIM];
	float		uy[VDIM];
	float		uz[VDIM];
}				t_basis;

void			vec_add(float src_a[VDIM], float src_b[VDIM], float dst[VDIM]);
void			vec_copy(float src[VDIM], float dst[VDIM]);
void			vec_cross(float src_a[VDIM], float src_b[VDIM], float dst[VDIM]);
float			vec_dot(float src_a[VDIM], float src_b[VDIM]);
float			vec_get_norme(float vec[VDIM]);
void			vec_normalise(float src[VDIM], float dst[VDIM]);
void			vec_scalar_prod(float src[VDIM], float factor, float dst[VDIM]);
void			vec_set(float vec[VDIM], float a, float b, float c);				// mouahahaha c'est juste lalable ou VDIM = 3 cette fonction
void			vec_sub(float src_a[VDIM], float src_b[VDIM], float dst[VDIM]);

void			vec3_init(float *vec, float v0, float v1, float v2);		// must change name
void			vec3_print(float vec[3]);									// must change name
void			vec3_print_str(float vec[3], char *str);					// must change name

void			mat_set_id(float mat[VDIM][VDIM]);
void			mat_set_one_rot(float mat[VDIM][VDIM], int id1, int id2, float ang);
void			mat_set_all_rot(float mat[VDIM][VDIM], float ang[VDIM]);
void			mat_mult_mat(float src_l[VDIM][VDIM], float src_r[VDIM][VDIM], float dst[VDIM][VDIM]);
void			mat_mult_vec(float mat[VDIM][VDIM], float vec_src[VDIM], float vec_dst[VDIM]);

void			basis_describe(t_basis *b);
void			basis_init(t_basis *b);
void			basis_normalise(t_basis *b);
void			basis_orthonormalise(t_basis *b);
void			basis_reset(t_basis *b);
void			basis_rot_x(t_basis *b, float ang);
void			basis_rot_y(t_basis *b, float ang);
void			basis_rot_z(t_basis *b, float ang);
void			basis_set(t_basis *b, float ux[VDIM], float uy[VDIM], float uz[VDIM]);
void			basis_vec_w2b(t_basis *b, float src[VDIM], float dst[VDIM]); // vec: World -> Basis
void			basis_vec_b2w(t_basis *b, float src[VDIM], float dst[VDIM]); // vec: Basis -> World

/////////// pobablement d'autre fichier -->

typedef	struct	s_drawline
{
	t_basis		*from;
	t_basis		*to;
	float		pos[VDIM];
	float		col[VDIM];
	float		diff_col[VDIM];
	float		diff_pos[VDIM];
}				t_drawline;

typedef	struct	s_cam
{
	t_basis		*b;
	//t_win		*w;
}				t_cam;

t_drawline		*drawline_init_change(t_basis *from, t_basis *to);
t_drawline		*drawline_init_pos(t_drawline *dr, float p1[VDIM], float p2[VDIM]);
t_drawline		*drawline_init_col(t_drawline *dr, float c1[VDIM], float c2[VDIM]);
void			draw_line(t_cam *c, t_drawline *dr);
void			cam_init(t_cam *c, float pos[VDIM], float ang[VDIM]);



#endif

/*
**	Alors il reste a faire:
**			- les fonction de dessin
**			- les fonction/gestion de hook souris
**				ca serrait un peu comme si on re faisait un systeme de fenetre youpi
**	
*/
