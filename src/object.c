/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:32:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/18 22:55:23 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

float	get_dist_plan(t_basis *cam, t_obj *plan, float ray_dir[3])
{
	float	dist;

	dist = (vec_dot(plan->dir, cam->pos) + plan->radius) / (vec_dot(plan->dir, ray_dir)) ;	
	return (dist = 0.0);
}

float	get_dist_sphere(t_basis *cam, t_obj *sphere, float ray_dir[3])
{
	float	dist;
	(void)cam;
	(void)sphere;
	(void)ray_dir;

	
	return (dist = 0.0);
}

float	get_dist_cylinder(t_basis *cam, t_obj *cylinder, float ray_dir[3])
{
	float	dist;
	(void)cam;
	(void)cylinder;
	(void)ray_dir;

	return (dist = 0.0);
}

float	get_dist_cone(t_basis *cam, t_obj *cone, float ray_dir[3])
{
	float	dist;
	(void)cam;
	(void)cone;
	(void)ray_dir;

	return (dist = 0.0);
}


/*
**	Pour dessiner la scene on va faire des baille.
**	il faut trouver l'objet le plus proche: z_buffer + (id_obj/type_obj)
**
*/
