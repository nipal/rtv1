/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:30:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/06 20:11:12 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cam_turn_left(t_basis *cam, float ang)
{
	basis_rot_y(cam, ang);
//	printf("left\n");
}

void	cam_turn_right(t_basis *cam, float ang)
{
	basis_rot_y(cam, -ang);
//	printf("right\n");
}

void	cam_turn_down(t_basis *cam, float ang)
{
	basis_rot_x(cam, ang);
//	printf("down\n");
}

void	cam_turn_up(t_basis *cam, float ang)
{
	basis_rot_x(cam, -ang);
//	printf("up\n");

}

//	MAIS du coup on refactorera plus tard
//	ou si non on a juste une copie dans la cam
void	cam_init_draw_func(t_env *e)
{
	// USELESS
	e->obj_dist[0] = get_dist_plan;
	e->obj_dist[1] = get_dist_sphere;
	e->obj_dist[2] = get_dist_cylinder;
	e->obj_dist[3] = get_dist_cone;

	e->obj_nrm[0] = get_normal_plan;
	e->obj_nrm[1] = get_normal_sphere;
	e->obj_nrm[2] = get_normal_cylinder;
	e->obj_nrm[3] = get_normal_cone;
}

void	cam_rot(t_basis *cam, int x, int y)
{
	(void)x;
	(void)y;
	(void)cam;
	// on decoupe l'ecran en 3.
	// en fonction de la hauteur
	// on regarde
}

void	reset_zbuff(t_mlx_win *w)
{
	int	i;
	int	max;

	max = w->size_x * w->size_y;
	i = 0;
	while (i < max)
	{
		w->z_buff[i].id = -1;
		w->z_buff[i].dist = -1;
		i++;
	}
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
	float	dist;
	float	best_dist;
	int		best_id;
	float		(**obj_dist)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);
//	(void)i;(void)dist;(void)best_dist;(void)best_id;(void)obj_dist;

	dist = -1;
	best_id = -1;
	best_dist = -1;
	obj_dist = item->obj_dist;
	i = 0;
//	printf("---------OBJ:%d\n", item->nb_obj);
	while (i < item->nb_obj)
	{
		dist = obj_dist[item->obj[i].type](item->obj + i, vec3_cast(item->cam->pos), ray_dir);
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
	zbuff->pos = obj_get_pos(vec3_cast(item->cam->pos), ray_dir, best_dist);
	zbuff->nrm = item->obj_nrm[item->obj[best_id].type](item->obj + best_id, zbuff->pos);
//	vec3_print_str(zbuff->nrm, "plan_nrm");
//	*/
}

void	find_normale(t_env *e)
{
	(void)e;
}

//	|
//	v
// 		on incremente la direction
// 		on teste sur tout les objet le quel est le plus pres pour
// 		 	apres faire les calcul de lumiere et tout et tout
// 		dir = i * dx + j * dy

static	inline	void	init_ray(t_item *item, t_vec3 *dir, t_vec3 *dx, t_vec3 *dy)
{
	t_basis	*cam;

	cam = item->cam;	
	*dir = vec3_add(vec3_cast(cam->ux), vec3_cast(cam->uy));
	*dir = vec3_scalar(*dir, -0.5);
	*dir = vec3_add(vec3_cast(cam->uz), *dir);
	*dx = vec3_scalar(vec3_cast(cam->ux), item->size_x / item->size_y / item->size_x);
	*dy = vec3_scalar(vec3_cast(cam->uy), 1.0 / item->size_y);
}

// si on a pas calculer la distance (au carre), on met -1
int		is_free_path(t_item *item, t_vec3 from, t_vec3 to, int self)
{
	t_obj	*obj;
	int		i;
	float		(**obj_dist)(t_obj *o, t_vec3 ray_pos, t_vec3 ray_dir);
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
		if (i == self && ++i)
			continue ;
		dist.v2 = obj_dist[obj[i].type](obj + i, from, dir);
		if (dist.v2 > 0 && dist.v2 < dist.v1)
			return (0);
		i++;
	}
	return (1);
}

//	phong: Ambient, difuse, speculaire
// is_free_path -> difuse, speculaire


float	light_specular_coef(t_vec3 nrm, t_vec3 ray_dir, t_vec3 light_dir)
{
	t_vec3	ray_opp;
	float	coef;
	
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

float	light_difuse_coef(t_vec3 nrm, t_vec3 ray_dir, t_vec3 light_dir, float dist2)
{
	float	coef;
	(void)ray_dir;
		
// TODO: find solution for light power
	coef = -(10 / (0.1 + dist2) * vec3_dot(light_dir, nrm));
	if (coef > 1)
		return (1);
	else if (coef < 0)
		return (0);
	return (coef);
}

// TODO: put into obj_strture to each object have its properties
typedef	struct	s_phong_coef
{
	float		ambient;
	float		diffuse;
	float		specular;
}				t_coef_fong;

int		set_color(t_vec3 col, float coef, float spec)
{
	int		color;
	t_vec3	c;
	
	c = vec3_scalar(col, coef);
	color = (int)(c.x + (255 - c.x) * spec) << 16 
		| (int)(c.y + (255 - c.y * spec)) << 8 
		| (int)(c.z + (255 - c.z) * spec);
	return (color);
}

int		get_phong_color(t_item *item, t_zbuff *zbuff, t_vec3 ray_dir)
{
	t_vec3		light_dir;
	float		dist2;
	t_coef_fong	coef = {0.05, 0.95, 1};  // may be change
	int			id;

	id = zbuff->id;
	/* pour chaque lumiere */ 
	light_dir = vec3_sub(item->light[0].pos, zbuff->pos);
	dist2 = vec3_dot(light_dir, light_dir);
	light_dir = vec3_normalise(light_dir);
	if (zbuff->dist < 0)
		return (0);
	// on met la difuse
	if (!is_free_path(item, zbuff->pos, item->light[0].pos, id))
		coef.diffuse = 0;
	coef.diffuse *= light_difuse_coef(zbuff->nrm, ray_dir, light_dir, dist2);
	coef.specular = 0;//light_specular_coef(zbuff->nrm, ray_dir, light_dir); 
	return (set_color(item->obj[id].col, coef.diffuse + coef.ambient, coef.specular));
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
		dir = vec3_sub(dir, vec3_cast(item->cam->ux));
		dir = vec3_add(dir, dy);
		j++;
	}
}
