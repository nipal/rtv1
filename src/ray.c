/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:42:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/25 12:58:00 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	On va refaire le system de lumiere
**	On va integrer le MULTI_CAM + MULTI_SPOT
**	On va aussi refaire toute les foncction en mode bien decouper
*/

/*
**	on done : 	- le l'equation de la drooite du rayon: depart + direction
**				- la liste des object
**				- la fonction de distance en focniton d'un type d'objet
**
**	on renvoie:	l'indice de l'objet avec lequel ion a eu un instersection
**
**	On peut donc s'en servir pour trouver quelle object serra illuminer et si il est eclairer
**	on dira que les 
*/

int		ray_obj_intersect(t_vec3 ray_pos, t_vec3 ray_dir, t_item *item)
{
	(void) ray_pos; (void)ray_dir; (void)item;
	return (-1);
}

void	ray_adapt_pos_dir(t_vec3 *ray_pos, t_vec3 *ray_dir, t_mat3 *rot_inv)
{
	(void) ray_pos; (void)ray_dir; (void)rot_inv;
}

t_vec3	ray_reflect(t_vec3 pt_reflect, t_vec3 ray_dir, t_vec3 nrm)
{
	t_vec3	reflect = {0, 0, 0};

	return (reflect);
}

//	En fait les manipulation de la couelur ne sont pas si intuitive avec la deconmposition en RGB, mais peut etre plus avec 'hsv' ou 'hsl'
//	...	idealement il faudrait pouvoir avoir une valleur de la puissance sur une range de 0 -> inf au lieu de 0 -> 1... et donc avec 1 / x
//	==> avec tan(x) et atan(x), on pourait s'ensortir
//	==> il faut juste 
//t_vec3	color_normalise(t_vec3 c)
//{
//	return (vec3_scalar(c, 1.0 / 255.0));
//}
//
//t_vec3	color_expand(t_vec3 c)
//{
//	return (vec3_scalar(c, 255.0));
//}
//
//t_vec3	color_syntetisis_additive(t_vec3 c1, t_vec3 c2)
//{
//	t_vec3	sum = {0, 0, 0};
//	
//			
//	// on normalise les les couleur => on prend la valeur (1 - VAL)
//	// en fait si j'ai 0.9 et 0.9 je veux 0.95
//	// si j'ai 0.1 et 0.1 je veux... moins
//	//
//	c1 = color_normalise(c1);
//	c2 = color_normalise(c2);
//	c1 = vec3_scalar(c1, -1);
//	c1 = vec3_add_scalar(c1, 1);
//	c2 = vec3_scalar(c2, -1);
//	c2 = vec3_add_scalar(c2, 1);
//	return (sum);
//}

// addittion de couleur, on aditione es couleur  la rache et on sature a 255??

t_vec3	color_syntetisis_substratcive(t_vec3 c1, t_vec3 c2)
{
	t_vec3	sum = {0, 0, 0};
	
	return (sum);
}


//	ambient :	 	intersection
//	diffuse	:		intersection x illuminer? X dot(nrm_surface, dir_light)
//	speculaire:		intersection x illuminer? X dot(ray_reflect, dir_light) ^ alpha 
