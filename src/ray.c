/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:42:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/30 22:22:41 by fjanoty          ###   ########.fr       */
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
		coef.diffuse = 0;
	coef.diffuse *= light_difuse_coef(zbuff->nrm, ray_dir, light_dir, dist2);
	coef.specular = 0;//light_specular_coef(zbuff->nrm, ray_dir, light_dir); 
	return (set_color(item->obj[id].col, coef.diffuse + coef.ambient, coef.specular));
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
		dir = vec3_sub(dir, vec3_scalar(item->cam->ux, ratio));
		dir = vec3_add(dir, dy);
		j++;
	}
}
