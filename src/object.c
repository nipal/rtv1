/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:32:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/26 15:45:37 by fjanoty          ###   ########.fr       */
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

void	ray_adapt_pos_dir(t_vec3 *ray_dir, t_vec3 *ray_pos, t_vec3 obj_pos, t_mat3 rot_inv)
{
	*ray_pos = mat3_mult_vec3(rot_inv, vec3_sub(*ray_pos, obj_pos));
	*ray_dir = vec3_normalise(mat3_mult_vec3(rot_inv, *ray_dir));
}

//						   |  GET_DIST 	|	
//	###################### V 			V ############################

//TODO Refacto les rotation de la lib quaterion
void	obj_set_invrot(t_obj *obj, double rx, double ry, double rz)
{
	(void)rz;
	obj->rot_inv = mat3_rot_all(-rx, -ry, 0);
}

////	la new pos de l'abjet est nul mais 
////TODO Refacto les rotation de la lib quaterion
//t_vec3	adapt_cam_pos(t_obj *obj, t_vec3 cam_pos)
//{
//	return (mat3_mult_vec3(obj->rot_inv, vec3_sub(cam_pos, obj->pos)));
//}
//
////TODO Refacto les rotation de la lib quaterion
//t_vec3	adapt_ray_dir(t_obj *obj, t_vec3 ray_dir)
//{
//	return (mat3_mult_vec3(obj->rot_inv, ray_dir));
//}

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

//	si on test sans les corection, on doit avoir l'objet en 0 et de dir uz
double	get_dist_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	ray_adapt_pos_dir(&ray_dir, &ray_pos, cylinder->pos, cylinder->rot_inv);
	a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y;
	b = 2 * (ray_dir.x * ray_pos.x + ray_dir.y * ray_pos.y);
	c = ray_pos.x * ray_pos.x + ray_pos.y * ray_pos.y - cylinder->value * cylinder->value;
	return (solve_eq_2nd(a, b, c));
}

double	get_dist_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	ray_adapt_pos_dir(&ray_dir, &ray_pos, cone->pos, cone->rot_inv);
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
	t_vec3	out;

	out = vec3_scalar(ray_dir, dist);
	out = vec3_add(out, ray_pos);
	return (out);
}

//						   |   GET_NORMAL 	|	
//	###################### V 				V ############################
t_vec3	get_normal_plan(t_obj *plan, t_vec3 pos_impact)
{
	t_vec3	out;

	//	c'est directement la normale du plan
	(void)pos_impact;
	out = vec3_scalar(plan->dir, 1);
//	ft_memmove(out, plan->dir, sizeof(t_vec3) * 3);
	return (out);
}

t_vec3	get_normal_sphere(t_obj *sphere, t_vec3 pos_impact)
{
	t_vec3	out;

	//	du centre de la sphere auy point d'impact
	out = vec3_sub(pos_impact, sphere->pos);
	out = vec3_normalise(out);
	out = vec3_scalar(out, -1);
	return (out);
}

t_vec3	get_normal_cylinder(t_obj *cylinder, t_vec3 pos_impact)
{
	t_vec3	out;
	double	coef;
	t_vec3	u;

	u = vec3_sub(pos_impact, cylinder->pos);
	coef = -vec3_dot(cylinder->dir, u) / vec3_dot(cylinder->dir, cylinder->dir); // normalement la direction est normaliser donc pas trop besoin de diviser par un truc qui ferra 1
	out = vec3_scalar(cylinder->dir, coef);
	out = vec3_add(out, u);
	out = vec3_normalise(out);
//	out = vec3_normalise(vec3_add(vec3_scalar(cylinder->dir, coef), u));
	return (out);
}

//	c'est juste le coeficient qui change que on obten 0 avec un produit sclaire different
t_vec3	get_normal_cone(t_obj *cone, t_vec3 pos_impact)
{
	t_vec3	out;
	double	coef;
	t_vec3	u;	// impacte - origin
	
	u = vec3_sub(pos_impact, cone->pos);
	coef = -(vec3_dot(u, u)) / vec3_dot(cone->dir, u);
	out = vec3_scalar(cone->dir, coef);
	out = vec3_add(out, u);
	out = vec3_normalise(out);
//	out = vec3_normalise(vec3_add(vec3_scalar(cylinder->dir, coef), u));
	return (out);
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

// la il faut recuperer les multiple intersection positive
/*
**	z: nb_solus
**	x: dist 1
**	y: dist 2
**
**	Si il une distance n'est pas defini on laisse la valeur negative
*/

t_vec3	eq_2nd_get_all_solution(double a, double b, double c)
{
	double	delta;
	t_vec3	solus;

	solus = vec3_set(-1, -1, 0);
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (solus);
	delta = sqrt(delta);
	if ((solus.x = (-delta - b) / (2 * a)) >= 0)
		solus.z++;
	if ((solus.y = (delta - b) / (2 * a)) >= 0)
		solus.z++;
	return (solus);
}

/*
**	le plan ne peu pas se faire de l'ombre sur lui meme
*/

t_vec3	dist_all_plan(t_obj *plan, t_vec3 ray_pos, t_vec3 ray_dir)
{
	(void)plan;
	(void)ray_pos;
	(void)ray_dir;
	return (vec3_set(-1, -1, 0));
}

t_vec3	dist_all_sphere(t_obj *sphere, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	a = vec3_dot(ray_dir, ray_dir);
	b = 2 * (vec3_dot(ray_dir, ray_pos) - vec3_dot(ray_dir, sphere->pos));
	c = vec3_dot(ray_pos, ray_pos) + vec3_dot(sphere->pos, sphere->pos) - 2 * vec3_dot(ray_pos, sphere->pos) - sphere->value * sphere->value;
	return (eq_2nd_get_all_solution(a, b, c));
}

//	si on test sans les corection, on doit avoir l'objet en 0 et de dir uz
t_vec3	dist_all_cylinder(t_obj *cylinder, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	ray_adapt_pos_dir(&ray_dir, &ray_pos, cylinder->pos, cylinder->rot_inv);
	a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y;
	b = 2 * (ray_dir.x * ray_pos.x + ray_dir.y * ray_pos.y);
	c = ray_pos.x * ray_pos.x + ray_pos.y * ray_pos.y - cylinder->value * cylinder->value;
	return (eq_2nd_get_all_solution(a, b, c));
}

t_vec3	dist_all_cone(t_obj *cone, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double	a;
	double	b;
	double	c;

	ray_adapt_pos_dir(&ray_dir, &ray_pos, cone->pos, cone->rot_inv);
	a = RD0 * RD0 + RD1 * RD1 - RD2 * RD2 * cone->value;
	b = 2 * (RD0 * RP0 + RD1 * RP1 - RD2 * RP2 * cone->value);
	c = RP0 * RP0 + RP1 * RP1 - RP2 * RP2 * cone->value;
	return (eq_2nd_get_all_solution(a, b, c));
}
