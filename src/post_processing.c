/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:34:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/31 00:01:40 by fjanoty          ###   ########.fr       */
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
	proj.x = (int)(((vec3_dot(vec, vec3_scalar(w->cam->ux, ratio)) / proj.z) * w->size_x) - w->size_x / 2);
	proj.y = (int)(((vec3_dot(vec, w->cam->uy) / proj.z) * w->size_y) - w->size_y / 2);
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

	x = (int)pos.x;
	y = (int)pos.y;
	if (x >= 0 && x < w->size_x && y >= 0 && y < w->size_y)
	{
		w->data[x + y * w->size_x].nb = pp_vec_to_color(col);
	} 
}

//	pos.x , pos.y => le centre le la sphere
//	pos.z sont radius
void	pp_draw_circle(t_mlx_win *w, t_vec3 pos, t_vec3 col)
{
	int	i;
	int	j;

	j = (int)(pos.y - (pos.z * 0.5));
	while (j < ((int)(pos.y + (pos.z * 0.5))))
	{
		i = (int)(pos.x - (pos.z * 0.5));
		while (i < ((int)(pos.x + (pos.z * 0.5))))
		{
			if (sqrt((i - pos.x) * (i - pos.x) + (j - pos.y) * (j - pos.y)) <= pos.z)
				pp_put_pix(w, vec3_set(i, j, 0), col);
			i++;
		}
	}
}

void	pp_draw_light(t_mlx_win *w, t_light *l, double radius, t_vec3 col)
{
	//	On va representer la lumiere comme une sphere
	//
	//	dans le repaire de la camera: ou ce trouve la position?
	//	----------------------------: quelle est la taille de la sphere?
	//	parcourir le carre en question => en ne depassant pas du buffer_image
	//	et avoir une fonction de coloration sympa
	//	ET incruster la sphere selon le zbuffer
	t_vec3	pos;
	int		i;
	int		j;
	int		id;

	pos	= pp_screen_proj_coord(w, l->pos);
	radius = (int)(radius / pos.z);

	pp_draw_circle(w, vec3_set(100, 100, 20), vec3_set(255, 255, 0));
	return ;

	j = pos.y - (radius * 0.5);
//	printf();
	while (j < (pos.y + (radius * 0.5)))
	{
		i = pos.x - radius * 0.5;
		while (i < (pos.x + radius * 0.5))
		{
			id = i + j * w->size_x;
			printf("i:%d	j:%d		id:%d\n", i, j, id);
			if (id >= 0 && id <= (w->size_x * w->size_y) && pp_is_circle(pos, radius, i, j))
			{
				w->data[id].nb = pp_get_light_color(radius, (double)i - pos.x, (double)j - pos.y, col);
			}
			i++;
		}
	}
}
//	on pourra comparer la taille avec une sphere que l'on raytrace

void	pp_draw_segment(t_mlx_win *w, t_vec3 from, t_vec3 to, t_vec3 color)
{
	(void)w; (void)from;(void)to;(void)color;
	//	dans le repaire de la camera: ou ce trouve les deux point?
	//	Ou se trouve le debut et la fin... Est-ce qu'on dessine tout
	//	parcourir le carre en question => en ne depassant pas du buffer_image
	//	et avoir une fonction de coloration sympa
	//	ET incruster la sphere selon le zbuffer
}

/*
**	Ou est-ce qu'on stoque toute les ligne
**	comment est-ce qu'on les cree
**	comment on en ajoute
**	comment en enleve? --> est-ce qu'on permet ca?
**	c'est quoi l'instance qui les manage?
*/
