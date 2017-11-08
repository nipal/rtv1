/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_porcessing_draw.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:34:56 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:38:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

	pos = pp_screen_proj_coord(w, l->pos);
	radius = (radius / pos.z) * w->size_y;
	if (pos.z > 0)
		pp_draw_circle(w, pos, radius, col);
}

void	pp_draw_segment(t_mlx_win *w, t_vec3 from, t_vec3 to, t_vec3 color)
{
	int		i;
	double	max;
	t_vec3	dir_scr;
	t_vec3	dir_world;
	t_vec3	pt;

	dir_world = vec3_sub(to, from);
	pt = pp_screen_proj_coord(w, from);
	to = pp_screen_proj_coord(w, to);
	dir_scr = vec3_sub(to, pt);
	max = (int)2 * (sqrt(dir_scr.x * dir_scr.x + dir_scr.y * dir_scr.y));
	dir_scr = vec3_scalar(dir_scr, 1.0 / max);
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
