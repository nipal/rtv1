/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:34:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 05:42:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	renvoie les coordonnee projeter sur l'ecran
**	donc (x, y)	=> ceux de l'ecran
**	z 			=> la distance a l'ecran
*/
t_vec3	pp_screen_proj_coord(t_mlx_win *w, t_vec3 vec)
{
	t_vec3	proj;
	double	ratio;
	
	ratio = w->size_x / w->size_y;
	vec = vec3_sub(vec, w->cam->pos);
	proj.z = vec3_dot(vec, w->cam->uz);
	proj.x = (int)(((vec3_dot(vec, vec3_scalar(w->cam->ux, 1)) / (proj.z * ratio)) * w->size_x) + w->size_x / 2);
	proj.y = (int)(((vec3_dot(vec, w->cam->uy) / proj.z) * w->size_y) + w->size_y / 2);
	return (proj);
}

int		pp_is_circle(t_vec3 pos, double radius, double x, double y)
{
	x = x - pos.x;
	y = y - pos.y;
	if (sqrt(x * x + y * y) <= radius)
		return (1);
	return (0);
}

int		pp_get_light_color(double radius, double x, double y, t_vec3 col)
{
	(void)radius; (void)x; (void)y;
	// on fera plus tard un truc sympa sur les bord de la sphere
	return (((int)(col.x) << 16) |
			((int)(col.y) << 8) |
			((int)(col.z)));
}

int		pp_vec_to_color(t_vec3 col)
{
	return (((int)(col.x) << 16) |
			((int)(col.y) << 8) |
			((int)(col.z)));
}

void	pp_put_pix(t_mlx_win *w, t_vec3 pos, t_vec3 col)
{
	int	x;
	int	y;
	int	id;

	x = (int)pos.x;
	y = (int)pos.y;
	id = x + y * w->size_x;
	if (mlx_win_is_inside(w, x, y) &&
		(w->zbuff[id].dist < 0  || pos.z < w->zbuff[id].dist))
	{
		w->data[id].nb = pp_vec_to_color(col);
		w->zbuff[id].dist = pos.z;
		//	il faudrait aussi metre a jour d'autre valeur... ou pas
	}
}

//	pos.x , pos.y => le centre le la sphere
//	pos.z sont radius
void	pp_draw_circle(t_mlx_win *w, t_vec3 pos, double radius, t_vec3 col)
{
	int		i;
	int		j;
	double	x;
	double	y;

	j = (int)(pos.y - (radius));
	while (j < ((int)(pos.y + (radius))) && j >= 0 && j < w->size_y)
	{
		i = (int)(pos.x - (radius));
		while (i < ((int)(pos.x + (radius))) && i >= 0 && i < w->size_x)
		{
			x = i - pos.x;
			y = j - pos.y;
			if (sqrt(x * x + y * y) <= radius)
				pp_put_pix(w, vec3_set(i, j, pos.z), col);
			i++;
		}
		j++;
	}
}

void	pp_draw_light_flat(t_mlx_win *w, t_light *l, double radius, t_vec3 col)
{
	t_vec3	pos;

	pos	= pp_screen_proj_coord(w, l->pos);
	radius = (radius / pos.z) * w->size_y;
	if (pos.z > 0)
		pp_draw_circle(w, pos, radius, col);
}

/*
**	En entrer on a deux point dans e repere du monde
**	nous on va traduire ces coordoner dans le repere de la camera
**	et on va tranquilement dessinner la ligne entre ces deux point
**
**	C'est dans une autre fonction que on va manager la creation, le stoquge
**		et ordonner l'affichage, donc les appelle a cette fonction
*/
void	pp_draw_segment(t_mlx_win *w, t_vec3 from, t_vec3 to, t_vec3 color)
{
	int		i;
	double	max;
	t_vec3	dir_screen;
	t_vec3	dir_world;
	t_vec3	pt;

	dir_world = vec3_sub(to, from);
	pt = pp_screen_proj_coord(w, from);
	to = pp_screen_proj_coord(w, to);
	dir_screen = vec3_sub(to, pt);
	max = (int)2 * (sqrt(dir_screen.x * dir_screen.x + dir_screen.y * dir_screen.y));
	dir_screen = vec3_scalar(dir_screen, 1.0 / max);
	dir_world = vec3_scalar(dir_world, 1.0 / max);
	i = 0;
	if (pt.z >= 0 && to.z >= 0
			&& max < 10 * ((w->size_x > w->size_y) ? w->size_x : w->size_y))
		while (i < max)
		{
			from = vec3_add(from, dir_world);
			pt = pp_screen_proj_coord(w, from);
			pt.z = vec3_norme(vec3_sub(from, w->cam->pos));
			pp_put_pix(w, pt, color); 
			i++;
		}
}

void	pp_draw_segment2(t_mlx_win *w, t_vec3 from, t_vec3 to, t_vec3 color)
{
	int		i;
	double	max;
	t_vec3	dir;

	to = pp_screen_proj_coord(w, to);
	from = pp_screen_proj_coord(w, from);
	dir = vec3_sub(to, from);
	max = (sqrt(dir.x * dir.x + dir.y * dir.y));
	dir = vec3_scalar(dir, 1.0 / max);
	i = 0;
	if (from.z >= 0 && to.z >= 0
			&& max < 5 * ((w->size_x > w->size_y) ? w->size_x : w->size_y))
		while (i < max)
		{
			from = vec3_add(from, dir);
			pp_put_pix(w, from, color); 
			i++;
		}
}


	
/*
**	(1)	:Ou est-ce qu'on stoque toute les ligne
**	(2)	:comment est-ce qu'on les cree
**	(3)	:comment on en ajoute
**	(4)	:comment en enleve? --> est-ce qu'on permet ca?
**	(5)	:c'est quoi l'instance qui les manage?
**	(6)	: A quelle moment, dans quel condition tout ca
**			--> genre pour un normale a un obj...
*/


/*
**	(1)	=>	on stoque tout dans des liste
**	(2)	=>	avec une fonction 
**	(3)	=>	foction de list: lst_add_front (pck + rapide)
**	(4)	=>	on a des fonction generique de liste... 
**	(5)	=>	un structur t_seg
*/
