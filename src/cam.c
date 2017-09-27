/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:30:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/28 00:37:18 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cam_turn_left(t_basis *cam, float ang)
{
	basis_rot_y(cam, ang);
	printf("left\n");
}

void	cam_turn_right(t_basis *cam, float ang)
{
	basis_rot_y(cam, -ang);
	printf("right\n");
}

void	cam_turn_down(t_basis *cam, float ang)
{
	basis_rot_x(cam, ang);
	printf("down\n");
}

void	cam_turn_up(t_basis *cam, float ang)
{
	basis_rot_x(cam, -ang);
	printf("up\n");

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
	int		nb_obj;
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
	nb_obj = item->nb_obj;
	i = 0;
	while (i < nb_obj)
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

int		get_color(t_item *item, t_zbuff *zbuff, float ray_dir[3])
{
	(void)item;
	(void)zbuff;
	(void)ray_dir;
	int	color;
	float	dist2;
	float	light_dir[3];
	float	coef;
		
	if (zbuff->dist < 0)
		return (0);
	/* pour chaque lumiere */ 
	vec_sub(item->light[0].pos, zbuff->pos, light_dir);
	dist2 = vec_dot(light_dir, light_dir);
	vec_normalise(light_dir, light_dir);
	if (is_free_path(item, zbuff->pos, item->light[0].pos, zbuff->id))
	{
//		printf("FREE_path\n");
		// need check si need mult by -1
		coef = -(20 / (1 + dist2) * item->light[0].power * vec_dot(ray_dir, zbuff->nrm));
		coef = (coef > 1) ? 1 : coef;
		coef = (coef < 0) ? 0 : coef;
		color = (int)(coef * item->obj[zbuff->id].col[0]) << 16
			| (int)(coef * item->obj[zbuff->id].col[1]) << 8
			| (int)(coef * item->obj[zbuff->id].col[2]); 
//		printf("coef:%f	color:%d\n", coef, color);
	}
	else
	{
//		printf("NO_free_path\n");
		color = 0;
	}
	return (color);
}

void	fill_zbuff(t_mlx_win *w, t_item *item)
{
	int		i;
	int		j;
	float	dir[3];
//	float	dir_nrm[3];
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
//			vec_normalise(dir, dir);
			find_collision(w->z_buff + i + j * w->size_x, item, dir);
			w->data[i + j * w->size_x].nb = get_color(item, w->z_buff + i + j * w->size_x, dir);
			i++;
		}
		vec_sub(dir, item->cam->ux, dir);
		vec_add(dir, dy, dir);
		j++;
	}
}

//	|
//	|
//	v	=========== Old way to define pixel's color

// On fait une serie d'adition et de soustraction de vecteur. C'est bien pour
// le nombre d'operation mais on peu cummuler des erreur lier aux imprecision
// des calcule avec des float. En faisant a chaque fois une multiplication en plus
// on a pas d'ereur qui se cumule.

int		get_test_color(t_mlx_win *w, int i, float color)
{
	int	col;
		/* ici le  calcule de lumiere */
		color = w->z_buff[i].dist;	
		if (color <= 0)
			color = 0;
		else
			w->data[i].nb = 0;
//		printf("color:%f	x:%d	y:%d\n", color, (i % w->size_x), (i / w->size_x));
		col = (int)(color * 255) << 16 | (int)(color * 255) << 8 | ((int)(color * 255));
		return (col);
}

/*
**	On a besoin du rayon, 
*/

int		define_color()
{
	int	col;

	col = 0;
	return (col);
}

// On pourrai aussi ne faire qu'une seule boucle...
void	color_scene(t_mlx_win *w, t_light *light, t_obj *obj)
{
	// on va juste doner une couleur en fpnction des objet
	int		i;
	int		j;
	int		max;
	int		col;
	(void)obj;
	(void)light;
	(void)j;

	i = 0;
	max = w->size_x * w->size_y;
	while (i < max)
	{
		j = 0;
		col = 0;
		while (light[j].power >= 0)
		{
			col = define_color();
			j++;
		}
		w->data[i].nb = get_test_color(w, i, w->z_buff[i].dist);
		i++;
	}
}

/*
**	Pour la coloration.
**	Il faut des lumiere:	
**		
*/
