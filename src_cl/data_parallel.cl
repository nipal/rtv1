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

# define WIDTH		5
# define HEIGHT		5

float	get_sphere_distance(float3 pos_s, float size_s, float3 pos_c, float3 dir_c)
{
	float	dist;
	float3	vecto;
	float3	diff;

	diff = pos_s - pos_c;

	vecto.x = dir_c.y * diff.z - dir_c.z * diff.y;
	vecto.y = dir_c.z * diff.x - dir_c.x * diff.z;
	vecto.z = dir_c.x * diff.y - dir_c.y * diff.x;
	dist = sqrt(dot(vecto, vecto)) / sqrt(dot(dir_c, dir_c));
	return (dist);
}

float	dist_sphere_cam(float3 diff, float3 dir)
{
	float	dist;
	float	dist2;
	float	a;
	float	b;
	float	c;
	float	delta;

	a = dot(dir, dir);
	b = 2. * dot(dir, diff);
	c = dot(diff, diff);
	delta = b * b - 4 * a * c;
	if (delta < 0 || a == 0)
		return (-1);
	delta = sqrt(delta);
	dist = (-b - delta) / (2 * a);
	dist2 = (-b + delta) / (2 * a);
	if (dist * dist2 < 0)
	{
		if (dist > 0)
			return (dist);
		return (dist2);
	}
	if (dist > 0)
	{
		if (dist > dist2)
			return (dist2);
		return (dist);
	}
	return (-1);
}

//	float4	get_sphere_normale(float4 pos_s, float4 pos_c, float4 dir_c, float dist)
//	{
//		// on prolonge le vecteur directeur par la distance
//		// on ajoute a la position de la camera			=>	on a le point d'intersection.
//		//	on lui soustrait la position de la sphere 	=>	on a la dorection	
//	}
//	
//	
//		dist = norme(dir vectoriel diff) / norme(dir_c);
//	
//		vecto.x = dir_c.y * diff.z - dir_c.z * diff.y;
//		vecto.y = dir_c.z * diff.x - dir_c.x * diff.z;
//		vecto.z = dir_c.x * diff.y - dir_c.y * diff.x;
//	


__kernel void test_image(__global int* time, __global int* data)
{
	int	id = get_global_id(0);
	int	val;
	
	val = (id + *time) % 256;
	data[id] = ((val * 7)% 256) << 16 | (256 - val) << 8 | abs(128 - val) * 2;
}

//	
//	[ , , ] pos
//	
//	[ , , ]	: ux
//	[ , , ]	: uy
//	[ , , ]	: uz
//	


__kernel void define_ray_dir(__global float4* dir, __global float4* landmark)
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
}
