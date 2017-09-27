/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:32:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/27 19:07:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

/*
**	on va mettre dans le value la valur du 'd' de l'eq cartesienne du plan
*/

void	ray_adapt(t_obj *obj, float ray_src[3], float ray_dst[3])
{
	mat_mult_vec(obj->rot_inv, ray_src, ray_dst);
}

void	plan_init(t_obj *plan)
{
	plan->value = -vec_dot(plan->dir, plan->pos);	
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
//	printf("a:%f	b:%f	c:%f	r1:%.20f	r2:%.20f\n", a, b, c, r1, r2);
	if (r1 < 0 && r2 < 0)
		return (-1);
	if (r1 < 0)
		return (r2);
	if (r2 < 0)
		return (r1);
	return ((r1 < r2) ? r1 : r2);
}

//						   |  GET_DIST 	|	
//	###################### V 			V ############################

void	obj_set_invrot(t_obj *obj, float rx, float ry, float rz)
{
	float	rot_dir[3][3];
	float	ang[3];

	obj->ang[0] = -rx;
	obj->ang[1] = -ry;
	obj->ang[2] = -rz;
	mat_set_all_rot(obj->rot_inv, obj->ang);
	ang[0] = rx;
	ang[1] = ry;
	ang[2] = rz;
	mat_set_all_rot(rot_dir, ang);
	vec_set(obj->dir, 0, 0, 1);
	mat_mult_vec(rot_dir, obj->dir, obj->dir);
}

//	la new pos de l'abjet est nul mais 
void	adapt_cam_pos(t_obj *obj, float cam_pos[3], float new_pos[3])
{
	vec_sub(cam_pos, obj->pos, new_pos);
	mat_mult_vec(obj->rot_inv, new_pos, new_pos);
}

void	adapt_ray_dir(t_obj *obj, float ray_dir[3], float ray_result[3])
{
	mat_mult_vec(obj->rot_inv, ray_dir, ray_result);
}

float	get_dist_plan(t_obj *plan, float ray_pos[3], float ray_dir[3])
{
	float	dist;

	dist = -(vec_dot(plan->dir, ray_pos) + plan->value) / (vec_dot(plan->dir, ray_dir)) ;	
	return (dist);
}

float	get_dist_sphere(t_obj *sphere, float ray_pos[3], float ray_dir[3])
{
	float	dist;
	float	a;
	float	b;
	float	c;

	a = vec_dot(ray_dir, ray_dir);
	b = 2 * (vec_dot(ray_dir, ray_pos) - vec_dot(ray_dir, sphere->pos));
	c = vec_dot(ray_pos, ray_pos) + vec_dot(sphere->pos, sphere->pos) - 2 * vec_dot(ray_pos, sphere->pos) - sphere->value * sphere->value;
	dist = solve_eq_2nd(a, b, c);
	return (dist);
}

float	get_dist_cylinder(t_obj *cylinder, float ray_pos[3], float ray_dir[3])
{
	float	a;
	float	b;
	float	c;
	float	ray_pos2[3];
	float	ray_dir2[3];

	// must adapte position then orientation
	// ray_pos2 = ray_pos - obj->pos;
	vec_sub(ray_pos, cylinder->pos, ray_pos2);
	mat_mult_vec(cylinder->rot_inv, ray_dir, ray_dir2);
	a = ray_dir2[0] * ray_dir2[0] + ray_dir2[1] * ray_dir2[1];
	b = 2 * (ray_dir2[0] * ray_pos2[0] + ray_dir2[1] * ray_pos2[1]);
	c = ray_pos2[0] * ray_pos2[0] + ray_pos2[1] * ray_pos2[1] - cylinder->value * cylinder->value;
	return (solve_eq_2nd(a, b, c));
}

float	get_dist_cone(t_obj *cone, float ray_pos[3], float ray_dir[3])
{
	float	a;
	float	b;
	float	c;
	float	ray_pos2[3]; // on pourrai laisser le r2 (cone->radisu)
	float	ray_dir2[3];

	// must adapte position then orientation
	vec_sub(ray_pos, cone->pos, ray_pos2);
	mat_mult_vec(cone->rot_inv, ray_dir, ray_dir2);
	a = RD0 * RD0 + RD1 * RD1 - RD2 * RD2 * cone->value;
	b = 2 * (RD0 * RP0 + RD1 * RP1 - RD2 * RP2 * cone->value);
	c = RP0 * RP0 + RP1 * RP1 - RP2 * RP2 * cone->value;
	return (solve_eq_2nd(a, b, c));
}

//						   |     SET_POS	|	
//	###################### V 				V ############################

//	bug si deux fois le meme objet
void	obj_set_pos(float ray_pos[3], float ray_dir[3], float dist, float result[3])
{
	// rayon normalise ? ... c'est aussi celui qui a servie
	vec_scalar_prod(ray_dir, dist, result);
	vec_add(result, ray_pos, result);
}

//						   |   GET_NORMAL 	|	
//	###################### V 				V ############################
void	set_normal_plan(t_obj *plan, float pos_impact[3], float result[3])
{
	//	c'est directement la normale du plan
	(void)pos_impact;
	ft_memmove(result, plan->dir, sizeof(float) * 3);
}

void	set_normal_sphere(t_obj *sphere, float pos_impact[3], float result[3])
{
	//	du centre de la sphere auy point d'impact
	vec_sub(pos_impact, sphere->pos, result);
	vec_normalise(result, result);
}

void	set_normal_cylinder(t_obj *cylinder, float pos_impact[3], float result[3])
{
	float	coef;
	float	u[3];

	vec_sub(pos_impact, cylinder->pos, u);
	coef = vec_dot(cylinder->dir, u);
	vec_scalar_prod(cylinder->dir, coef, result);
	vec_add(result, cylinder->pos, result);
	vec_sub(pos_impact, result, result);
	vec_normalise(result, result);
}

void	set_normal_cone(t_obj *cone, float pos_impact[3], float result[3])
{
	float	coef;
	float	u[3];	// impacte - origin
	
	vec_sub(pos_impact, cone->pos, u);
	coef = -(vec_dot(u, u)) / vec_dot(cone->dir, u);
	vec_scalar_prod(cone->dir, coef, result);
	vec_add(result, u, result);
	vec_normalise(result, result);
}
/*
 
	// ca depent de l'orientation qui a ete faite
	//	si on a donner une correction au rayon en position et en orientation
	//	alors il faut trouver le point d'impacte avec le rayon originel
	//	et la normal
	//
	//
	//	La normale est forcement perpendiculaire a la direction du cylindre
	//
	//	on peut le trouver la normale pour un cas ideal: centrer sur l'axe "z"
	//	et on applique la tranformation inverse a l'impacte trouver et a la normale
	//	
	//	Dans quelle base est definie l'impacte?
	//
	//	Monde reel:
	//		impact - ((pt_cylindre => impact) dot dir_cylindre_nrm) * dir_cylindre_nrm + pt_cylindre.
	//	Monde ideal:(dir paralele a uz, et centre)
	//		[nrm(impact(x, y))] --> transformation inverse ((tr, rot, tr))
	//


 		CONE
	//	Base de l'impact?
	//
	//	Monde reel:
	//
	//		
	//	Monde ideal: (dir paralele a uz, et centre)
	//
	//	I ==> imact quand on est centrer en 0
	//	dir = (I.x, Y.y, (Y.x^2 + Y.y^2) / Y.z) 
	//	ensuite on peu norme
	//		
	//	
	//	
	//	Si on connais l'angle de la pente 

	// monde reel: k, (k*dir + u) . u = 0 

*/

/*
**	Pour dessiner la scene on va faire des baille.
**	il faut trouver l'objet le plus proche: z_buffer + (id_obj/type_obj)
**
*/
