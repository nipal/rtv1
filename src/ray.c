/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:42:18 by fjanoty           #+#    #+#             */
/*   Updated: 2018/02/17 18:17:12 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	light_specular_coef(t_vec3 nrm, t_vec3 ray_dir, t_vec3 light_dir
		, double pow_spec)
{
	t_vec3	ray_opp;
	double	coef;

	ray_opp = ray_reflect(ray_dir, nrm);
	coef = vec3_dot(light_dir, ray_opp);
	if (coef >= 0)
		return (0);
	coef = (pow_spec >= 3) ? pow(-coef, pow_spec) : 0;
	if (coef < 0.01)
		return (0);
	return (coef);
}

double	light_difuse_coef(t_vec3 nrm, t_vec3 light_dir
		, double dist2)
{
	double	coef;
	double	a;

	a = fabs(vec3_dot(vec3_normalise(light_dir), vec3_normalise(nrm)));
	coef = ((3 / (0.01 + dist2)) * a);
	if (coef > 1)
		return (1);
	else if (coef < 0)
		return (0);
	return (coef);
}

void	init_ray(t_item *item, t_vec3 *dir, t_vec3 *dx, t_vec3 *dy)
{
	t_cam	*cam;
	double	ratio;

	if (item->size_x <= 0 || item->size_y <= 0)
	{
		perror("resolution error\n");
		exit(0);
	}
	ratio = item->size_x / item->size_y;
	cam = item->cam;
	*dx = vec3_scalar(cam->ux, 1.0 / (item->size_x) * ratio);
	*dy = vec3_scalar(cam->uy, 1.0 / item->size_y);
	*dir = vec3_add3(cam->uz, vec3_scalar(cam->ux, -0.5 * ratio)
			, vec3_scalar(cam->uy, -0.5));
}

void	launch_ray(t_mlx_win *w, t_item *item)
{
	int		i;
	int		j;
	t_vec3	d;
	t_mat3	all;

	init_ray(item, &d, &all.ux, &all.uy);
	j = -1;
	while (++j < w->size_y)
	{
		i = -1;
		while (++i < w->size_x)
		{
			d = vec3_add(d, all.ux);
			all.uz = vec3_normalise(d);
			find_collision(w->zbuff + i + j * w->size_x, item, all.uz);
			w->data[i + j * w->size_x].nb =
				get_phong_color(item, w->zbuff + i + j * w->size_x, all.uz);
		}
		d = vec3_add(vec3_sub(d, vec3_scalar(item->cam->ux, w->ratio)), all.uy);
	}
}
