/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:32:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/20 18:55:26 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

/*
**	on va mettre dans le radius la valur du 'd' de l'eq cartesienne du plan
*/

void	ray_adapt(t_obj *obj, float ray_adapted[3], float ray[3])
{
	(void)ray_adapted;
	(void)ray;
	(void)obj;
}

void	plan_init(t_obj *plan)
{
	plan->radius = -vec_dot(plan->dir, plan->pos);	
}



float	get_min2(float a, float b)
{
	return ((a < b) ? a : b);
}

float	get_min3(float a, float b, float c)
{
	float	min;

	min = (a < b) ? a : b;
	min = (c < min) ? c : min;
	return (min);
}

// il faut renvoyer le plus petit resulta positif
float	solve_eq_2nd(float a, float b, float c)
{
	float	delta;
	float	r1;
	float	r2;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1);
	delta = sqrt(delta);
	r1 = (-delta - b) / (2 * a);
	r2 = (delta - b) / (2 * a);
	if (r1 < 0 && r2 < 0)
		return (-1);
	if (r1 < 0)
		return (r2);
	if (r2 < 0)
		return (r1);
	return ((r1 < r2) ? r1 : r2);
}

float	get_dist_plan(t_basis *cam, t_obj *plan, float ray_dir[3])
{
	float	dist;

	dist = (vec_dot(plan->dir, cam->pos) + plan->radius) / (vec_dot(plan->dir, ray_dir)) ;	
	return (dist = 0.0);
}

float	get_dist_sphere(t_basis *cam, t_obj *sphere, float ray_dir[3])
{
	float	dist;
	float	a;
	float	b;
	float	c;

	a = vec_dot(ray_dir, ray_dir);
	b = 2 * (vec_dot(ray_dir, cam->pos) - vec_dot(ray_dir, sphere->pos));
	c = vec_dot(cam->pos, cam->pos) + vec_dot(sphere->pos, sphere->pos) - 2 * vec_dot(cam->pos, sphere->pos) - sphere->radius * sphere->radius;
	dist = solve_eq_2nd(a, b, c);
	if (dist != 0)
	{
//		if (dist > 0)
//			printf("		");
//		printf("dist:%f\n", dist);
	}
	return (dist);
}

float	get_dist_cylinder(t_basis *cam, t_obj *cylinder, float ray_dir[3])
{
	float	dist;
	float	a;
	float	b;
	float	c;

	// must adapte position then orientation
	a = ray_dir[0] * ray_dir[0] + ray_dir[1] * ray_dir[1];
	b = 2 * (ray_dir[0] * cam->pos[0] + ray_dir[1] * cam->pos[1]);
	c = cam->pos[0] * cam->pos[0] + cam->pos[1] * cam->pos[1] - cylinder->radius * cylinder->radius;
	dist = solve_eq_2nd(a, b, c);
	return (dist);
}

float	get_dist_cone(t_basis *cam, t_obj *cone, float ray_dir[3])
{
	float	dist;
	float	a;
	float	b;
	float	c;

	// must adapte position then orientation
	a = ray_dir[0] * ray_dir[0] + ray_dir[1] * ray_dir[1];
	b = 2 * (ray_dir[0] * cam->pos[0] + ray_dir[1] * cam->pos[1]) - cone->radius * cone->radius *ray_dir[2];
	c = cam->pos[0] * cam->pos[0] + cam->pos[1] * cam->pos[1] - cone->radius * cone->radius * cam->pos[1];
	dist = solve_eq_2nd(a, b, c);
	return (dist);
}


void	set_position(float ray_dir[3], float ray_pos[3], float dist, float new_pos[3])
{

	vec_scalar_prod(ray_dir, dist, new_pos);
	vec_add(new_pos, ray_pos, new_pos);
}

/*
**	Pour dessiner la scene on va faire des baille.
**	il faut trouver l'objet le plus proche: z_buffer + (id_obj/type_obj)
**
*/
