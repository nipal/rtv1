/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:42:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/29 20:56:30 by fjanoty          ###   ########.fr       */
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

/*
**	On veux savoir si les deux normale sont du meme cote du plan normale a la direction de la lumiere
**	nrm1, nrm2, light_dir
*/

int	is_opposite_side(t_vec3 nrm1, t_vec3 nrm2, t_vec3 light_dir)
{
	if (debug_ray)
	{
		printf("is_opposite_side:	%s\n", ((vec3_dot(nrm1, light_dir) * vec3_dot(nrm2, light_dir)) < 0) ? "YES" : "no");
	}
	if ((vec3_dot(nrm1, light_dir) * vec3_dot(nrm2, light_dir)) < 0)
		return (1);
	return (0);
}

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

//	si la lumiere et la vue sont du meme cote de la normal
int		is_light_right_side(t_vec3 ray_dir, t_vec3 light_dir, t_vec3 normal)
{
	ray_dir = vec3_normalise(ray_dir);
	light_dir = vec3_normalise(light_dir);
	normal = vec3_normalise(normal);
//	return (1);
	if (debug_ray)
	{
		printf("is_light_right_side:	%s\n", ((vec3_dot(normal, ray_dir) * vec3_dot(normal, light_dir)) > 0) ? "YES" : "NO");
	}
	if ((vec3_dot(normal, ray_dir) * vec3_dot(normal, light_dir)) > 0)
		return (1);
	return (0);
}

int		is_self_intersect(t_item *item, t_vec3 from, t_vec3 to, int self)
{
	t_vec3	solus;
	t_vec3	(**obj_dist_all)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);
	t_obj	*obj;
	t_vec3	dir;
	t_vec3	pt1, pt2, nrm1, nrm2, nrm_now;
	double	dist;
	(void)pt1; (void)pt2;(void)nrm1; (void)nrm2;(void)nrm_now;
//	int	inter_s1, inter_s2;

//return (0);
	dist = vec3_norme((dir = vec3_sub(to, from)));
	dir =  vec3_normalise(dir);
	obj = item->obj + self;
	obj_dist_all = item->obj_dist_all;
	solus = obj_dist_all[obj->type](obj, from, dir);
//	pt1 = obj_get_pos(from, dir, solus.x);
//	pt2 = obj_get_pos(from, dir, solus.y);
//	nrm1 = item->obj_nrm[obj->type](obj, pt1);
//	nrm2 = item->obj_nrm[obj->type](obj, pt2);
//	nrm_now = item->obj_nrm[obj->type](obj, from);
	if (debug_ray)
	{
		printf("self_instersect	%s\n", ((solus.x > ZERO_P && solus.x < dist) || (solus.y > ZERO_P && solus.y < dist)) ? "YES": "NO ");	
		printf("	s1:%f	dist:%f	=> %s\n", solus.x, dist, (solus.x > ZERO_P && solus.x < dist) ? "SHADOW" : "--");
		printf("	s2:%f	dist:%f	=> %s\n", solus.y, dist, (solus.y > ZERO_P && solus.y < dist) ? "SHADOW" : "--");
//	printf("s1:%.25f	dist:%.25f	s1:%s 	dot_now:%.25f	dot_s1:%.25f\n", solus.x, dist, (solus.x > ZERO_P && solus.x < dist) ? "TRUE " : "false", vec3_dot(nrm_now, dir), vec3_dot(nrm1, dir));
//	printf("s2:%.25f	dist:%.25f	s2:%s 	dot_now:%.25f	dot_s2:%.25f\n", solus.y, dist, (solus.y > ZERO_P && solus.y < dist) ? "TRUE " : "false", vec3_dot(nrm_now, dir), vec3_dot(nrm2, dir));

	}
//	if (((solus.x > 0 && solus.x < dist))
//		|| ((solus.y > 0 && dist < dist)))
//	printf("s1:%.15f	dist:%.15f	s1:%s 	dot_now:%.15f	dot_s1:%.15f\n", solus.x, dist, (solus.x > 0 && solus.x < dist) ? "TRUE " : "false", vec3_dot(nrm_now, dir), vec3_dot(nrm1, dir));
//	printf("s2:%.15f	dist:%.15f	s2:%s 	dot_now:%.15f	dot_s2:%.15f\n", solus.y, dist, (solus.y > 0 && solus.y < dist) ? "TRUE " : "false", vec3_dot(nrm_now, dir), vec3_dot(nrm2, dir));
	if (((solus.x > ZERO_P && solus.x < dist) /*&& is_opposite_side(nrm_now, nrm1, dir) */)
		|| ((solus.y > ZERO_P && solus.y < dist) /*&& is_opposite_side(nrm_now, nrm2, dir)*/))
		return (1);
	return (0);
}

// si on a pas calculer la distance (au carre), on met -1
int		is_free_path(t_item *item, t_vec3 from, t_vec3 to, int self)
{
	t_obj	*obj;
	int		i;
	double		(**obj_dist)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3	dir;
	t_val	dist;

	dir = vec3_sub(to, from);
	dist.v1 = vec3_dot(dir, dir);
	dist.v1 = sqrt(dist.v1);
	dir = vec3_normalise(dir);
	obj_dist = item->obj_dist;
	obj = item->obj;
	i = 0;
	while (i < item->nb_obj)
	{
		(void)self;
		if (i == self && ++i)
		{
			if (is_self_intersect(item, from, to, self))
				return (0);
			continue ;
		}
		dist.v2 = obj_dist[obj[i].type](obj + i, from, dir);
		if ((float)dist.v2 > 1 && dist.v2 < dist.v1)
			return (0);
		i++;
	}
	return (1);
}

int		is_light(t_item *item, t_vec3 from, t_vec3 to, int self)
{
	if (!is_free_path(item, from, to, self))
		return (0);
	return (1);
}

//	phong: Ambient, difuse, speculaire
// is_free_path -> difuse, speculaire


double	light_specular_coef(t_vec3 nrm, t_vec3 ray_dir, t_vec3 light_dir)
{
	t_vec3	ray_opp;
	double	coef;
	
	// on construit le rayon reflechi
	coef = vec3_dot(nrm, ray_dir);
	ray_opp = vec3_scalar(nrm, coef);
	ray_opp = vec3_sub(ray_opp, ray_dir);
	ray_opp = vec3_scalar(ray_opp, 2);
	ray_opp = vec3_add(ray_dir, ray_opp);
	// on le compar au rayon lumineux
	coef = vec3_dot(ray_opp, light_dir);
	return ((coef > -0.999) ? 0 : -coef);
}

double	light_difuse_coef(t_vec3 nrm, t_vec3 ray_dir, t_vec3 light_dir, double dist2)
{
	double	coef;
	double a, b, c; (void)a; (void)b; (void)c;
	(void)ray_dir;
		
// TODO: find solution for light power
	a = fabs(vec3_dot(vec3_normalise(light_dir), vec3_normalise(nrm)));
	if (debug_ray)
	{
		printf("coef_difuse:%f\n", a);
	}
	coef = ((3 / (0.01 + dist2)) * a);
//	printf("coef_finale:%f	coef_dot_prod:%f\n", coef, a);
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

// coef = ambient + diffuse
// spec = cef_speculare
int		set_color(t_vec3 col, double coef, double spec)
{
	(void)spec;
	int		color;
	t_vec3	c;
	
//	printf("coef:%f\n", coef);
	c = vec3_scalar(col, coef);
//	vec3_print_str(c, "col:");
	color = (((int)(c.x)) << 16) | (((int)(c.y)) << 8) | (((int)(c.z))); 
//	color = (int)(c.x + (255 - c.x) * spec) << 16 
//		| (int)(c.y + (255 - c.y * spec)) << 8 
//		| (int)(c.z + (255 - c.z) * spec);
	return (color);
}

int		get_phong_color(t_item *item, t_zbuff *zbuff, t_vec3 ray_dir)
{
	t_vec3		light_dir;
	double		dist2;
	t_coef_fong	coef = {0.1, 0, 1};  // may be change
	int			id;

	coef.diffuse = 1 - coef.ambient;
	id = zbuff->id;
	/* pour chaque lumiere */ 
	light_dir = vec3_sub(item->light[0].pos, zbuff->pos);
	dist2 = vec3_dot(light_dir, light_dir);
	light_dir = vec3_normalise(light_dir);
	if (zbuff->dist < 0)
		return (0);
//		return (0x26053e); // on a toucher AUCUN objet la c'est du violet fonce
	if (!is_free_path(item, zbuff->pos, item->light[0].pos, id)
	   ||  !is_light_right_side(ray_dir, light_dir, zbuff->nrm))
	{
//		printf("youpi");
		coef.diffuse = 0;
	}
	coef.diffuse *= light_difuse_coef(zbuff->nrm, ray_dir, light_dir, dist2);
	coef.specular = 0;//light_specular_coef(zbuff->nrm, ray_dir, light_dir); 
	return (set_color(item->obj[id].col, coef.diffuse + coef.ambient, coef.specular));
}

void	init_ray(t_item *item, t_vec3 *dir, t_vec3 *dx, t_vec3 *dy)
{
	t_cam	*cam;

	cam = item->cam;
	*dir = vec3_add(cam->ux, cam->uy);
	*dir = vec3_scalar(*dir, -0.5);
	*dir = vec3_add(cam->uz, *dir);
	*dx = vec3_scalar(cam->ux, item->size_x / item->size_y / item->size_x);
	*dy = vec3_scalar(cam->uy, 1.0 / item->size_y);
}

void	launch_ray(t_mlx_win *w, t_item *item)
{
	int		i;
	int		j;
	t_vec3	dir;
	t_vec3	dir_nrm;
	t_vec3	dx;
	t_vec3	dy;

	init_ray(item, &dir, &dx, &dy);
//	vec3_print_str(dir, "dir:");
	j = 0;
	while (j < w->size_y)
	{
		i = 0;
		while (i < w->size_x)
		{
			dir = vec3_add(dir, dx);
			dir_nrm = vec3_normalise(dir);
			find_collision(w->z_buff + i + j * w->size_x, item, dir_nrm);
			w->data[i + j * w->size_x].nb = get_phong_color(item, w->z_buff + i + j * w->size_x, dir_nrm);
			i++;
		}
		dir = vec3_sub(dir, item->cam->ux);
		dir = vec3_add(dir, dy);
		j++;
	}
}
