/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:30:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/29 22:17:48 by fjanoty          ###   ########.fr       */
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

	e->obj_nrm[0] = set_normal_plan;
	e->obj_nrm[1] = set_normal_sphere;
	e->obj_nrm[2] = set_normal_cylinder;
	e->obj_nrm[3] = set_normal_cone;
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

void	find_collision(t_zbuff *zbuff, t_item *item, float ray_dir[3])
{
	(void)zbuff;
	(void)item;
	(void)ray_dir;
//	/*
	int		i;
	float	dist;
	float	best_dist;
	int		best_id;
	float		(**obj_dist)(t_obj *o, float ray_pos[3], float ray_dir[3]);
	(void)i;(void)dist;(void)best_dist;(void)best_id;(void)obj_dist;

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
	obj_set_pos(item->cam->pos, ray_dir, best_dist, zbuff->pos);
	item->obj_nrm[item->obj[best_id].type](item->obj + best_id, zbuff->pos, zbuff->nrm);
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

static	inline	void	init_ray(t_item *item, float dir[3], float dx[3], float dy[3])
{
	t_basis	*cam;

	cam = item->cam;	
	vec_add(cam->ux, cam->uy, dir);
	vec_scalar_prod(dir, -0.5, dir);
	vec_add(cam->uz, dir, dir);
	vec_scalar_prod(cam->ux, 1.0 / (float)item->size_x, dx);	
	vec_scalar_prod(cam->uy, 1.0 / (float)item->size_y, dy);
}

// si on a pas calculer la distance (au carre), on met -1
int		is_free_path(t_item *item, float from[3], float to[3], int self)
{
	t_obj	*obj;
	int		i;
	float		(**obj_dist)(t_obj *o, float ray_pos[3], float ray_dir[3]);
	float	dir[3];
	t_val	dist;

	vec_sub(to, from, dir);
	dist.v1 = vec_dot(dir, dir);
	dist.v1 = sqrt(dist.v1);
	vec_normalise(dir, dir);
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


float	light_specular_coef(float nrm[3], float ray_dir[3], float light_dir[3])
{
	float	ray_opp[3];
	float	coef;
	
	// on construit le rayon reflechi
	coef = vec_dot(nrm, ray_dir);
	vec_scalar_prod(nrm, coef, ray_opp);
	vec_sub(ray_opp, ray_dir, ray_opp);
	vec_scalar_prod(ray_opp, 2, ray_opp);
	vec_add(ray_dir, ray_opp, ray_opp);
	// on le compar au rayon lumineux
	coef = vec_dot(ray_opp, light_dir);
	return ((coef > -0.999) ? 0 : -coef);
}

float	light_difuse_coef(float nrm[3], float ray_dir[3], float light_dir[3], float dist2)
{
	float	coef;
	(void)ray_dir;
		
// TODO: find solution for light power
	coef = -(10 / (0.1 + dist2) * vec_dot(light_dir, nrm));
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

int		set_color(float col[3], float coef, float spec)
{
	int		color;
	float	c[3];
	
	vec_scalar_prod(col, coef, c);
	color = (int)(c[0] + (255 - c[0]) * spec) << 16 
		| (int)(c[1] + (255 - c[1] * spec)) << 8 
		| (int)(c[2] + (255 - c[2]) * spec);
	return (color);
}

int		get_phong_color(t_item *item, t_zbuff *zbuff, float ray_dir[3])
{
	float		light_dir[3];
	float		dist2;
	t_coef_fong	coef = {0.05, 0.95, 1};  // may be change
	int			id;

	id = zbuff->id;
	/* pour chaque lumiere */ 
	vec_sub(item->light[0].pos, zbuff->pos, light_dir);
	dist2 = vec_dot(light_dir, light_dir);
	vec_normalise(light_dir, light_dir);
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
	float	dir[3];
	float	dir_nrm[3];
	float	dx[3];
	float	dy[3];

	init_ray(item, dir, dx, dy);
	j = 0;
	while (j < w->size_y)
	{
		i = 0;
		while (i < w->size_x)
		{
			vec_add(dir, dx, dir);
			vec_normalise(dir, dir_nrm);
			find_collision(w->z_buff + i + j * w->size_x, item, dir_nrm);
			w->data[i + j * w->size_x].nb = get_phong_color(item, w->z_buff + i + j * w->size_x, dir_nrm);

			i++;
		}
		vec_sub(dir, item->cam->ux, dir);
		vec_add(dir, dy, dir);
		j++;
	}
}
