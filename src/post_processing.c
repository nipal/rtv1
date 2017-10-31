/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:34:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/31 18:06:23 by fjanoty          ###   ########.fr       */
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

	x = (int)pos.x;
	y = (int)pos.y;
	if (x >= 0 && x < w->size_x && y >= 0 && y < w->size_y)
	{
		w->data[x + y * w->size_x].nb = pp_vec_to_color(col);
	} 
}

//	pos.x , pos.y => le centre le la sphere
//	pos.z sont radius
void	pp_draw_circle(t_mlx_win *w, t_vec3 pos, double radius, t_vec3 col)
{
	int	i;
	int	j;
	double	x;
	double	y;

//	t_obj	light;
//	double	dist;
//	double		(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
//	t_vec3	ray_pos;
//	t_vec3	ray_dir;
//	double	ratio;
//	double	x1, y1;

//	ratio = w->size_x / w->size_y;
//	ray_pos = w->cam.pos; // en fait il faudrait la vrai position de la limire pour que ca fonctionne avec 
//	light.pos = ;
//	light.value = radius;
	j = (int)(pos.y - (radius));
	while (j < ((int)(pos.y + (radius))) && j >= 0 && j < w->size_y)
	{
		i = (int)(pos.x - (radius));
		while (i < ((int)(pos.x + (radius))) && i >= 0 && i < w->size_x)
		{
			x = i - pos.x;
			y = j - pos.y;
//			x1 = (double)i - (w->size_x / 2) * ratio;
//			y1 = (double)j - (w->size_y / 2);
//			ray_dir = vec3_normalise(vec3_add3(cam->uz, vec3_scalar(cam->ux, x1), vec3_scalar(cam->uy, y1)));
//			printf("x:%f	y:%f: r:%f	==> pt:%f\n", x, y, radius, sum);
			if ((w->z_buff[i + j * w->size_x].dist < 0  || pos.z <= w->z_buff[i + j * w->size_x].dist) && sqrt(x * x + y * y) <= radius)
				pp_put_pix(w, vec3_set(i, j, 0), col);
			i++;
		}
		j++;
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
//	int		i;
//	int		j;
//	int		id;

	pos	= pp_screen_proj_coord(w, l->pos);
	radius = (radius / pos.z) * w->size_y;
//	pos.z = 5;

//	vec3_print_str(pos, "pos_light_on_screen:");
//	printf("radius_size:%.20f\n", radius);
	// on pourrais aussi utiliser juste les fonction de pour tracer des sphere et comme ca on a tout
	// genre position, profondeur, la vie
	if (pos.z > 0)
		pp_draw_circle(w, pos, radius, col);
//	return ;
//
//	j = pos.y - (radius * 0.5);
////	printf();
//	while (j < (pos.y + (radius * 0.5)))
//	{
//		i = pos.x - radius * 0.5;
//		while (i < (pos.x + radius * 0.5))
//		{
//			id = i + j * w->size_x;
//			printf("i:%d	j:%d		id:%d\n", i, j, id);
//			if (id >= 0 && id <= (w->size_x * w->size_y) && pp_is_circle(pos, radius, i, j))
//			{
//				w->data[id].nb = pp_get_light_color(radius, (double)i - pos.x, (double)j - pos.y, col);
//			}
//			i++;
//		}
//	}
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
