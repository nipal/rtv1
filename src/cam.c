/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:30:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/19 17:47:09 by fjanoty          ###   ########.fr       */
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

// on enverra l'addresse decaler au bon endroi comme ca plus besoin de x, y
void	find_collision(t_env *e, t_zbuff *zbuff, t_obj *obj, float ray_dir[3])
{
	float	dist
	float	best_dist;
	int		best_type;

	best_type = -1;
	best_dist = -1;
	i = 0;
	while (obj[i].type >= 0)
	{
		dist = e->obj_dist[obj[i].type](e->cam, obj + i, ray_dir);
		if (dist > 0 && dist < best_dist && best_didst >= 0)
		{
			best_dist = dist;
			best_id = i;
		}
		i++;
	}
	zbuff[0].id = best_id;
	zbuff[0].dist = best_dist;
	// sur tout les objet on teste le rayon et un enregistre dans le z buffer l'object le plus proche
}

void	fill_zbuff(t_mlx_win *w, t_basis *cam, t_obj *obj)
{
	int		i;
	int		j;
	float	dir[3];
	float	dx[3];
	float	dy[3];

	// on initialise les increment
	// on initialise la direction en haut a gauche
	dir = cam->dz - cam->dx / 2 - cam->dy / 2;
	dx = cam->dx / size_x;
	dy = cam->dy / size_y;
	j = 0;
	while (j < w->size_y)
	{
		i = 0;
		while (i < w->size_x)
		{
			// on incremente la direction
			// on teste sur tout les objet le quel est le plus pres pour
			//		apres faire les calcul de lumiere et tout et tout
			
			dir += dx;
			i++;
		}
		dir -= cam->dx
		dir += dy;
		j++;
	}
}
// On fait une serie d'adition et de soustraction de vecteur. C'est bien pour
// le nombre d'operation mais on peu cummuler des erreur lier aux imprecision
// des calcule avec des float. En faisant a chaque fois une multiplication en plus
// on a pas d'ereur qui se cumule.
