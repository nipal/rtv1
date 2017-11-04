/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:42:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 15:21:21 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	color_syntetisis_substratcive(t_vec3 c1, t_vec3 c2)
{
	(void)c1; (void)c2;
	t_vec3	sum = {0, 0, 0};
	
	return (sum);
}

void	find_collision(t_zbuff *zb, t_it *it, t_vec3 ray_dir)
{
	int		i;
	double	dst;
	double	best_dist;
	int		best_id;
	double		(**obj_dist)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);

	dst = -1;
	best_id = -1;
	best_dist = -1;
	obj_dist = it->obj_dist;
	i = 0;
	while (i < it->nb_obj)
	{
		dst = obj_dist[it->obj[i].type](it->obj + i, it->cam->pos, ray_dir);
		if (dst > 0 && ((dst < best_dist && best_dist >= 0) || best_dist < 0))
		{
			best_dist = dst;
			best_id = i;
		}
		i++;
	}
	zb->id = best_id;
	zb->dist = best_dist;
	if (best_id < 0)
		return ;
	zb->pos = obj_get_pos(it->cam->pos, ray_dir, best_dist);
	zb->nrm = it->obj_nrm[it->obj[best_id].type](it->obj + best_id, zb->pos);
}

t_vec3	ray_reflect(t_vec3 ray_dir, t_vec3 normal)
{
	t_vec3	reflect;

	reflect = vec3_add(ray_dir, vec3_scalar(vec3_sub(vec3_scalar(
						normal, vec3_dot(ray_dir, normal)), ray_dir), 2));
	return (reflect);
}

double	light_specular_coef(t_vec3 nrm, t_vec3 ray_dir, t_vec3 light_dir
		, double pow_spec)
{
	t_vec3	ray_opp;
	double	coef;

	ray_opp = ray_reflect(ray_dir, nrm);	
	coef = vec3_dot(light_dir, ray_opp);
	if (coef >= 0)
		return (0);
	coef = (pow_spec >= 3) ? pow(-coef, pow_spec): 0;
	if (coef < 0.01)
		return (0);
	return (coef);
}

double	light_difuse_coef(t_vec3 nrm, t_vec3 ray_dir, t_vec3 light_dir
		, double dist2)
{
	double	coef;
	double a, b, c; (void)a; (void)b; (void)c;
	(void)ray_dir;
		
	a = fabs(vec3_dot(vec3_normalise(light_dir), vec3_normalise(nrm)));
	coef = ((3 / (0.01 + dist2)) * a);
	if (coef > 1)
		return (1);
	else if (coef < 0)
		return (0);
	return (coef);
}

typedef	struct	s_phong_coef
{
	double		ambient;
	double		diffuse;
	double		specular;
}				t_coef_fong;

t_vec3	color_mix(t_vec3 light, t_vec3 obj, double spec)
{
	return (vec3_add(vec3_scalar(light, spec), vec3_scalar(obj, 1 - spec)));
}

int		set_color(t_vec3 col, double coef, double spec, t_vec3 light_color)
{
	(void)spec;
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
	t_pix 	b;
	t_pix	sum;
	int		tmp;

	b.nb = c2;
	sum.comp[0] = ((tmp = a.comp[0] + b.comp[0]) > 255) ? 255 : tmp;
	sum.comp[1] = ((tmp = a.comp[1] + b.comp[1]) > 255) ? 255 : tmp;
	sum.comp[2] = ((tmp = a.comp[2] + b.comp[2]) > 255) ? 255 : tmp;
	sum.comp[3] = ((tmp = a.comp[3] + b.comp[3]) > 255) ? 255 : tmp;
	return (sum);
}

int		get_phong_color(t_item *item, t_zbuff *zbuff, t_vec3 ray_dir)
{
	t_vec3		light_dir;
	static	t_coef_fong	coef = {0.1, 0, 0.4};
	int			i;
	t_pix		sum_color;
	double		dist2;

	sum_color.nb = 0;
	i = -1;
	while (++i < item->nb_light)
	{
		coef.diffuse = 1 - coef.ambient;
		coef.specular = 1;
		light_dir = vec3_sub(item->light[i].pos, zbuff->pos);
		dist2 = vec3_dot(light_dir, light_dir);
		light_dir = vec3_normalise(light_dir);
		if (zbuff->dist < 0)
			return (0);
		if ((!is_free_path(item, zbuff->pos, item->light[i].pos, zbuff->id) && !(coef.specular = 0))
		   ||  !is_light_right_side(ray_dir, light_dir, zbuff->nrm))
			coef.diffuse = 0;
		coef.diffuse *= light_difuse_coef(zbuff->nrm, ray_dir, light_dir, dist2);
		coef.specular *= light_specular_coef(zbuff->nrm, ray_dir, light_dir,item->obj[zbuff->id].pow_spec); 
		sum_color = color_add(sum_color,
			set_color(item->obj[zbuff->id].col, coef.diffuse + coef.ambient, coef.specular, item->light[i].col));
	}
	return (sum_color.nb);
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
	t_vec3	dir;
	t_vec3	dir_nrm;
	t_vec3	dx;
	t_vec3	dy;
	double	ratio;

	init_ray(item, &dir, &dx, &dy);
	ratio = item->size_x / item->size_y;
	j = 0;
	while (j < w->size_y)
	{
		i = 0;
		while (i < w->size_x)
		{
			dir = vec3_add(dir, dx);
			dir_nrm = vec3_normalise(dir);
			find_collision(w->zbuff + i + j * w->size_x, item, dir_nrm);
			w->data[i + j * w->size_x].nb =
				get_phong_color(item, w->zbuff + i + j * w->size_x, dir_nrm);
			i++;
		}
		dir = vec3_sub(dir, vec3_scalar(item->cam->ux, ratio));
		dir = vec3_add(dir, dy);
		j++;
	}
}
