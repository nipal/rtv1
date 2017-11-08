/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:34:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:52:40 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	pp_screen_proj_coord(t_mlx_win *w, t_vec3 vec)
{
	t_vec3	proj;
	double	ratio;

	ratio = w->size_x / w->size_y;
	vec = vec3_sub(vec, w->cam->pos);
	proj.z = vec3_dot(vec, w->cam->uz);
	proj.x = (int)(((vec3_dot(vec, vec3_scalar(w->cam->ux, 1))
					/ (proj.z * ratio)) * w->size_x) + w->size_x / 2);
	proj.y = (int)(((vec3_dot(vec, w->cam->uy)
					/ proj.z) * w->size_y) + w->size_y / 2);
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
	(void)radius;
	(void)x;
	(void)y;
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
		(w->zbuff[id].dist < 0 || pos.z < w->zbuff[id].dist))
	{
		w->data[id].nb = pp_vec_to_color(col);
		w->zbuff[id].dist = pos.z;
	}
}
