/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parallel.cl                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/14 07:07:45 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define SPHERE 	0
# define PLAN 		1
# define CYLINDRE	2
# define CONE		3

# define WIDTH		10
# define HEIGHT		10

__global	

float	solve_2nd_equation_dist(float3 coef)
{
	float	dist;
	float	dist2;
	float	delta;
	float	mult;

	delta = coef.y * coef.y - 4 * coef.x * coef.z;
	if (delta < 0 || coef.x == 0)
		return (-1);
	delta = sqrt(delta);
	dist = (-coef.y - delta) / (2 * coef.x);
	dist2 = (-coef.y + delta) / (2 * coef.x);
	mult = dist * dist2;
	if (mult < 0 && dist > 0)
		return (dist);
	else if (mult < 0 && dist > 0)
		return (dist2);
	else if (dist > 0 && dist > dist2)
			return (dist2);
	else if (dist > 0 && dist < dist2)
		return (dist);
	return (-1);
}

float4	mat4_vect4_product(float16 mat_rot, float4 vect)
{
	return ((float4) (dot(mat_rot.s0123, vect)
					, dot(mat_rot.s4567, vect)
					, dot(mat_rot.s89ab, vect)
					, dot(mat_rot.scdef, vect)));
}

//	on considere les foyer sur le plan (x, y) 
float	get_ellipse_dist(float4 f1, float4 f2, float sumr, float4 ray_dir, float4 ray_diff)
{
	
}


float	get_sphere_line_distance(float4 pos_s, float size_s, float4 pos_c, float4 dir_c)
{
	float	dist;
	float4	vecto;
	float4	diff;
	diff = pos_s - pos_c;

	vecto.x = dir_c.y * diff.z - dir_c.z * diff.y;
	vecto.y = dir_c.z * diff.x - dir_c.x * diff.z;
	vecto.z = dir_c.x * diff.y - dir_c.y * diff.x;
	dist = sqrt(dot(vecto, vecto) / dot(dir_c, dir_c));
	return (dist);
}

float	dist_plan_cam(float4 diff, float4 dir_ray, float4 dir_plan)
{
	float	tmp;
	float	result;

	tmp = dot(dir_plan, dir_ray);
	if (tmp == 0)
		return (-1.);
	return (-dir_plan.w - dot(dir_plan, diff) / tmp);
}

float	dist_cylindre_cam(float4 diff, float4 ray, float size2)
{
	float	dist;
	float3	coef;

	coef = (float3)(dot(ray.xy, ray.xy),
					2. * dot(ray.xy, diff.xy),
					dot(diff.xy, diff.xy) - size2);
	dist = solve_2nd_equation_dist(coef);
	return (dist);
}

float	dist_cone_cam(float4 diff, float4 ray, float coef_cone)
{
	float	dist;
	float3	coef;

	diff.z *= -1. * sqrt(coef_cone);	//	les deux serront deja calculer
	ray.z *= -1. * sqrt(coef_cone);	//	ou au minmum la racine
	coef = (float3)(dot(ray, ray),
					2 * dot(ray, diff),
					dot(diff, diff));
	dist = solve_2nd_equation_dist(coef);
	return (dist);
}

float	dist_sphere_cam(float4 diff, float4 dir)
{
	float	dist;
	float3	coef;

	coef.x = dot(dir, dir);
	coef.y = 2. * dot(dir, diff);
	coef.z = dot(diff, diff);
	dist = solve_2nd_equation_dist(coef);
	return (dist);
}


__kernel void test_image(__global int *time, __global int *data)
{
	int	id = get_global_id(0);
	int	val;
	
	val = (id + *time) % 256;
	data[id] = ((val * 7)% 256) << 16 | (256 - val) << 8 | abs(128 - val) * 2;
}

__kernel void init_frame(__global float4 *dir, __global float4 *landmark, __global float2 *zbuffer_id)
{
	int		id;
	float	coefx;
	float	coefy;
	float	WW;
	float	HH;
	float	ww;
	float	hh;

	id = get_global_id(0);
	WW = WIDTH;
	HH = HEIGHT;
	ww = id % WIDTH;
	hh = id / WIDTH;
	coefx = -2 * (0.5f - (ww / WW));
	coefy = -2 * (0.5f - (hh / HH));
	dir[id] = coefx * landmark[1] + coefy * landmark[2] + landmark[3];
	zbuffer_id[id] = (float2)(-1, -1);	
}
