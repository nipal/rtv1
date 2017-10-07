/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:32:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/07 13:58:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

/*
**	on va mettre dans le value la valur du 'd' de l'eq cartesienne du plan
*/

/*
	Probably useless
t_vec3	ray_adapt(t_obj *obj, t_vec3 ray_src)
{
	return (mat3_mult_vec3(obj->rot_inv, ray_src));
}
*/

void	plan_init(t_obj *plan)
{
	plan->value = -vec3_dot(plan->dir, plan->pos);	
}



double	get_min2(double a, double b)
{
	return ((a < b) ? a : b);
}

double	get_min3(double a, double b, double c)
{
	double	min;

	min = (a < b) ? a : b;
	min = (c < min) ? c : min;
	return (min);
}

// il faut renvoyer le plus petit resulta positif
double	solve_eq_2nd(double a, double b, double c)
{
	double	delta;
	double	r1;
	double	r2;

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

//TODO Refacto les rotation de la lib quaterion
void	obj_set_invrot(t_obj *obj, double rx, double ry, double rz)
{
	double	rot_dir[3][3];
	double	ang[3];
	(void) (rx + ry + rz);
	(void)obj;
	(void)ang;
	(void)rot_dir;

	/*
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
	*/
}

//	la new pos de l'abjet est nul mais 
//TODO Refacto les rotation de la lib quaterion
t_vec3	adapt_cam_pos(t_obj *obj, t_vec3 cam_pos)
{
	return (mat3_mult_vec3(obj->rot_inv, vec3_sub(cam_pos, obj->pos)));
}

//TODO Refacto les rotation de la lib quaterion
t_vec3	adapt_ray_dir(t_obj *obj, t_vec3 ray_dir)
{
	return (mat3_mult_vec3(obj->rot_inv, ray_dir));
}

double	get_dist_plan(t_obj *plan, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	dist;

	dist = -(vec3_dot(plan->dir, ray_pos) + plan->value) / (vec3_dot(plan->dir, ray_dir)) ;	
	return (dist);
}

double	get_dist_sphere(t_obj *sphere, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	dist;
	double	a;
	double	b;
	double	c;

	a = vec3_dot(ray_dir, ray_dir);
	b = 2 * (vec3_dot(ray_dir, ray_pos) - vec3_dot(ray_dir, sphere->pos));
	c = vec3_dot(ray_pos, ray_pos) + vec3_dot(sphere->pos, sphere->pos) - 2 * vec3_dot(ray_pos, sphere->pos) - sphere->value * sphere->value;
	dist = solve_eq_2nd(a, b, c);
	return (dist);
}

double	get_dist_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;
	t_vec3	ray_pos2;
	t_vec3	ray_dir2;

	// must adapte position then orientation
	// ray_pos2 = ray_pos - obj->pos;
	ray_pos2 = vec3_sub(ray_pos, cylinder->pos);
	ray_dir2 = mat3_mult_vec3(cylinder->rot_inv, ray_dir);
	a = ray_dir2.x * ray_dir2.x + ray_dir2.y * ray_dir2.y;
	b = 2 * (ray_dir2.x * ray_pos2.x + ray_dir2.y * ray_pos2.y);
	c = ray_pos2.x * ray_pos2.x + ray_pos2.y * ray_pos2.y - cylinder->value * cylinder->value;
	return (solve_eq_2nd(a, b, c));
}

double	get_dist_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;
	t_vec3	ray_pos2; // on pourrai laisser le r2 (cone->radisu)
	t_vec3	ray_dir2;

	// must adapte position then orientation
	ray_pos2 = vec3_sub(ray_pos, cone->pos);
	ray_dir2 = mat3_mult_vec3(cone->rot_inv, ray_dir);
	a = RD0 * RD0 + RD1 * RD1 - RD2 * RD2 * cone->value;
	b = 2 * (RD0 * RP0 + RD1 * RP1 - RD2 * RP2 * cone->value);
	c = RP0 * RP0 + RP1 * RP1 - RP2 * RP2 * cone->value;
	return (solve_eq_2nd(a, b, c));
}

//						   |     GET_POS	|	
//	###################### V 				V ############################

//	bug si deux fois le meme objet
// TODO need refacto return
t_vec3	obj_get_pos(t_vec3 ray_pos, t_vec3 ray_dir, double dist)
{
	t_vec3	result;

	result = vec3_scalar(ray_dir, dist);
	result = vec3_add(result, ray_pos);
	return (result);
}

//						   |   GET_NORMAL 	|	
//	###################### V 				V ############################
t_vec3	get_normal_plan(t_obj *plan, t_vec3 pos_impact)
{
	t_vec3	result;

	//	c'est directement la normale du plan
	(void)pos_impact;
	result = vec3_scalar(plan->dir, 1);
//	ft_memmove(result, plan->dir, sizeof(t_vec3) * 3);
	return (result);
}

t_vec3	get_normal_sphere(t_obj *sphere, t_vec3 pos_impact)
{
	t_vec3	result;

	//	du centre de la sphere auy point d'impact
	result = vec3_sub(pos_impact, sphere->pos);
	result = vec3_normalise(result);
	result = vec3_scalar(result, -1);
	return (result);
}

t_vec3	get_normal_cylinder(t_obj *cylinder, t_vec3 pos_impact)
{
	t_vec3	result;
	double	coef;
	t_vec3	u;

	u = vec3_sub(pos_impact, cylinder->pos);
	coef = vec3_dot(cylinder->dir, u);
	result = vec3_scalar(cylinder->dir, coef);
	result = vec3_add(result, cylinder->pos);
	result = vec3_sub(pos_impact, result);
	result = vec3_normalise(result);
	result = vec3_scalar(result, -1);
	return (result);
}

t_vec3	get_normal_cone(t_obj *cone, t_vec3 pos_impact)
{
	t_vec3	result;
	double	coef;
	t_vec3	u;	// impacte - origin
	
	u = vec3_sub(pos_impact, cone->pos);
	coef = -(vec3_dot(u, u)) / vec3_dot(cone->dir, u);
	result = vec3_scalar(cone->dir, coef);
	result = vec3_add(result, u);
	result = vec3_normalise(result);
	result = vec3_scalar(result, -1);
	return (result);
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
