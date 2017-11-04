/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:42:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 08:51:21 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


// addittion de couleur, on aditione es couleur  la rache et on sature a 255??

t_vec3	color_syntetisis_substratcive(t_vec3 c1, t_vec3 c2)
{
	(void)c1; (void)c2;
	t_vec3	sum = {0, 0, 0};
	
	return (sum);
}


//	ambient :	 	intersection
//	diffuse	:		intersection x illuminer? X dot(nrm_surface, dir_light)
//	speculaire:		intersection x illuminer? X dot(ray_reflect, dir_light) ^ alpha 



// on enverra l'addresse decaler au bon endroi comme ca plus besoin de x, y

/*
**	On definie
**		la distance
**		l'objet toucher
**		le point d'impacte
**		la normale a la surface
**	
*/

void	find_collision(t_zbuff *zbuff, t_item *item, t_vec3 ray_dir)
{
//	/*
	int		i;
	double	dist;
	double	best_dist;
	int		best_id;
	double		(**obj_dist)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);
//	(void)i;(void)dist;(void)best_dist;(void)best_id;(void)obj_dist;

	dist = -1;
	best_id = -1;
	best_dist = -1;
	obj_dist = item->obj_dist;
	i = 0;
//	printf("---------OBJ:%d\n", item->nb_obj);
	while (i < item->nb_obj)
	{
		dist = obj_dist[item->obj[i].type](item->obj + i, item->cam->pos, ray_dir);
		if (dist > 0 && ((dist < best_dist && best_dist >= 0) || best_dist < 0))
		{
			best_dist = dist;
			best_id = i;
		}
		i++;
	}
	zbuff->id = best_id;
	zbuff->dist = best_dist;
	if (best_id < 0)
		return ;
	zbuff->pos = obj_get_pos(item->cam->pos, ray_dir, best_dist);
	zbuff->nrm = item->obj_nrm[item->obj[best_id].type](item->obj + best_id, zbuff->pos);
//	vec3_print_str(zbuff->nrm, "plan_nrm");
//	*/
}



//	phong: Ambient, difuse, speculaire
// is_free_path -> difuse, speculaire

//	pour recuperer le rayon reflechis
t_vec3	ray_reflect(t_vec3 ray_dir, t_vec3 normal)
{
//	double	coef;
//	t_vec3	tmp;
//	t_vec3	tmp2;

//	coef = vec3_dot(ray_dir, normal);
//	tmp = vec3_scalar(normal, coef);
//	tmp2 = vec3_sub(tmp, ray_dir);
//	reflect = vec3_add(ray_dir, vec3_scalar(tmp2, 2));

	t_vec3	reflect;

	reflect = vec3_add(ray_dir, vec3_scalar(vec3_sub(vec3_scalar(
						normal, vec3_dot(ray_dir, normal)), ray_dir), 2));
	return (reflect);
//	return (vec3_add(ray_dir, vec3_scalar(vec3_sub(
//			vec3_scalar(normal, vec3_dot(ray_dir, normal)), ray_dir), 2)));
}

double	light_specular_coef(t_vec3 nrm, t_vec3 ray_dir, t_vec3 light_dir, double pow_spec)
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

double	light_difuse_coef(t_vec3 nrm, t_vec3 ray_dir, t_vec3 light_dir, double dist2)
{
	double	coef;
	double a, b, c; (void)a; (void)b; (void)c;
	(void)ray_dir;
		
// TODO: find solution for light power
	a = fabs(vec3_dot(vec3_normalise(light_dir), vec3_normalise(nrm)));
	coef = ((3 / (0.01 + dist2)) * a);
	if (coef > 1)
		return (1);
	else if (coef < 0)
		return (0);
	return (coef);
}

// TODO: put into obj_strture to each object have its properties
typedef	struct	s_phong_coef
{
	double		ambient;
	double		diffuse;
	double		specular;
}				t_coef_fong;

//	coef_1 => [0, 1]
t_vec3	color_mix(t_vec3 light, t_vec3 obj, double spec)
{
	return (vec3_add(vec3_scalar(light, spec), vec3_scalar(obj, 1 - spec)));
}

// coef = ambient + diffuse
// spec = cef_speculare
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

//int		get_phong_color(t_item *item, t_zbuff *zbuff, t_vec3 ray_dir)
//{
//	t_vec3		light_dir;
//	double		dist2;
//	t_coef_fong	coef = {0.1, 0, 1};  // may be change
//	int			id;
//
//	coef.diffuse = 1 - coef.ambient;
//	id = zbuff->id;
//	/* pour chaque lumiere */ 
//	light_dir = vec3_sub(item->light[0].pos, zbuff->pos);
//	dist2 = vec3_dot(light_dir, light_dir);
//	light_dir = vec3_normalise(light_dir);
//	if (zbuff->dist < 0)
//		return (0);
////		return (0x26053e); // on a toucher AUCUN objet la c'est du violet fonce
//	if (!is_free_path(item, zbuff->pos, item->light[0].pos, id)
//	   ||  !is_light_right_side(ray_dir, light_dir, zbuff->nrm))
//		coef.diffuse = 0;
//	coef.diffuse *= light_difuse_coef(zbuff->nrm, ray_dir, light_dir, dist2);
//	coef.specular = light_specular_coef(zbuff->nrm, ray_dir, light_dir); 
//	return (set_color(item->obj[id].col, coef.diffuse + coef.ambient, coef.specular));
//}

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
	static	t_coef_fong	coef = {0.1, 0, 0.4};  // may be change c'est un truc propre a l'objet
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
	ratio = item->size_x / item->size_y;			// a mettre dans la structure cam ... plus simple pour le desin apres (comme ux et uy)
	cam = item->cam;
	*dx = vec3_scalar(cam->ux, 1.0 / (item->size_x) * ratio);
	*dy = vec3_scalar(cam->uy, 1.0 / item->size_y);
	*dir = vec3_add3(cam->uz, vec3_scalar(cam->ux, -0.5 * ratio), vec3_scalar(cam->uy, -0.5));
//
//	*dir = vec3_add(vec3_scalar(cam->ux, ratio * -0.5), vec3_scalar(cam->uy, -0.5));
////	*dir = vec3_scalar(*dir, -0.5);
//	*dir = vec3_add(cam->uz, *dir);
//	*dx = vec3_scalar(cam->ux, 1.0 / (item->size_x));
//	*dy = vec3_scalar(cam->uy, 1.0 / item->size_y);
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
			w->data[i + j * w->size_x].nb = get_phong_color(item, w->zbuff + i + j * w->size_x, dir_nrm);
			i++;
		}
		dir = vec3_sub(dir, vec3_scalar(item->cam->ux, ratio));
		dir = vec3_add(dir, dy);
		j++;
	}
}
