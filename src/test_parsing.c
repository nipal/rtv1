/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:45:06 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/07 13:58:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*

typedef	struct	s_light
{
	double		pos[3];
	double		col[3];					// pour l'instant osef
	double		power;					// poura etre une condition d'arret si negatif
}				t_light;


typedef	struct	s_obj
{
	int			type;
	double		col[3];					// pour l'instant comme on connais [0, 255] juste ca changera plus tard
	double		rot_inv[3][3];
	double		ang[3];	// on peut reconstruire ses transformation
	double		pos[3];
	double		dir[3];
	double		value;
}				t_obj;


typedef	struct	s_basis
{
	double	pos[3];
	double*	axes[VDIM];
	double	ux[VDIM];
	double	uy[VDIM];
	double	uz[VDIM];
}				t_basis;




*/

//name, nature, offset, 

/*
**	On a une "cible" a trouver dans le texte
**	
*/
typedef	struct	s_rtv1_parse
{
	char		*obj_name;		// repere dans le text
	int			obj_type;		// repere dans pour un pointeur sur fonction
	size_t		offset;			// offset pour structure
}				t_rtv1_parse;

// {
// 		{"pos", TYPE_VEC, (&o->pos - &o)}
// 		{""}
// 		};
//

void	parsing_init()
{
	t_obj	o;

	t_rtv1_parse obj[6];

	(void)o;
	(void)obj;

}
