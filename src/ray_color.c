/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:41:35 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:43:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	color_mix(t_vec3 light, t_vec3 obj, double spec)
{
	return (vec3_add(vec3_scalar(light, spec), vec3_scalar(obj, 1 - spec)));
}

int		set_color(t_vec3 col, double coef, double spec, t_vec3 light_color)
{
	int		color;
	t_vec3	c;
	t_vec3	l;

	l = vec3_scalar(light_color, 1.0 / 255);
	col = vec3_set(l.x * col.x, l.y * col.y, l.z * col.z);
	c = vec3_scalar(col, coef);
	c = color_mix(light_color, c, spec);
	color = (((int)(c.x)) << 16) | (((int)(c.y)) << 8) | (((int)(c.z)));
	return (color);
}

t_pix	color_add(t_pix a, int c2)
{
	t_pix	b;
	t_pix	sum;
	int		tmp;

	b.nb = c2;
	sum.comp[0] =
		((tmp = a.comp[0] + b.comp[0]) > 255) ? 255 : tmp;
	sum.comp[1] =
		((tmp = a.comp[1] + b.comp[1]) > 255) ? 255 : tmp;
	sum.comp[2] =
		((tmp = a.comp[2] + b.comp[2]) > 255) ? 255 : tmp;
	sum.comp[3] =
		((tmp = a.comp[3] + b.comp[3]) > 255) ? 255 : tmp;
	return (sum);
}

int		get_one_color(t_item *item, t_zbuff *zbuff, t_vec3 ray_dir,
				t_light *light)
{
	t_vec3				light_dir;
	static	t_coef_fong	coef = {0.05, 0, 0.4};
	double				dist2;

	coef.dif = 1 - coef.amb;
	coef.spec = 1;
	light_dir = vec3_sub(item->light->pos, zbuff->pos);
	dist2 = vec3_dot(light_dir, light_dir);
	light_dir = vec3_normalise(light_dir);
	if (zbuff->dist < 0)
		return (0);
	if ((!is_free_path(item, zbuff->pos, light->pos, zbuff->id))
		|| !is_light_right_side(ray_dir, light_dir, zbuff->nrm))
	{
		coef.spec = 0;
		coef.dif = 0;
	}
	coef.dif *= light_difuse_coef(zbuff->nrm, light_dir, dist2);
	coef.spec *= light_specular_coef(zbuff->nrm, ray_dir, light_dir,
			item->obj[zbuff->id].pow_spec);
	return (set_color(item->obj[zbuff->id].col, coef.dif + coef.amb,
				coef.spec, light->col));
}

int		get_phong_color(t_item *item, t_zbuff *zbuff, t_vec3 ray_dir)
{
	int			i;
	t_pix		sum_color;

	sum_color.nb = 0;
	i = -1;
	while (++i < item->nb_light)
	{
		sum_color = color_add(sum_color,
			get_one_color(item, zbuff, ray_dir, item->light + i));
	}
	return (sum_color.nb);
}
