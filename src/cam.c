/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:30:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/18 22:53:19 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cam_init_draw_func(t_env *e)
{
	e->obj_dist[0] = get_dist_plan;
	e->obj_dist[1] = get_dist_sphere;
	e->obj_dist[2] = get_dist_cylinder;
	e->obj_dist[3] = get_dist_cone;
}

void	cam_rot(t_basis *cam, int x, int y)
{
	(void)x;
	(void)y;
	(void)cam;
	// on decoupe l'ecran en 3.
	// en fonction de la hauteur
	// on regarde
}

void	reset_zbuff(t_mlx_win *w)
{
	int	i;
	int	max;

	max = w->size_x * w->size_y;
	i = 0;
	while (i < max)
	{
		w->z_buff[i].id = -1;
		w->z_buff[i].dist = -1;
		i++;
	}
}

void	fill_zbuff(t_mlx_win *w, t_basis *cam, t_obj *obj)
{
	int		i;
	int		j;
	float	dir[3];
	(void)dir;
	(void)cam;
	(void)obj;

	// on initialise la direction au coin en haut a gauche
	j = 0;
	while (j < w->size_y)
	{
		i = 0;
		while (i < w->size_x)
		{
			// on incremente la direction
			// on teste sur tout les objet le quel est le plus pres pour
			//		apres faire les calcul de lumiere et tout et tout
			i++;
		}
		j++;
	}
}
