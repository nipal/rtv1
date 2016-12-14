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

__kernel void dataParallel(__global float* A, __global float* B, __global float* C)
{
	int base = 4*get_global_id(0);
	C[base+0] = A[base+0] + B[base+0];
	C[base+1] = A[base+1] - B[base+1];
	C[base+2] = A[base+2] * B[base+2];
	C[base+3] = A[base+3] / B[base+3];
}

__kernel void test_image(__global int *time, __global int* data)
{
	int	id = get_global_id(0);
	int	val;
	
	val = (id + *time) % 256;
	data[id] = val << 16 | (256 - val) << 8 | abs(128 - val) * 2;
}

float	get_sphere_distance(float3 pos_s, float size_s, float3 pos_c, float3 dir_c)
{
	float	dist;
	float3	vecto;
	float3	diff;

	diff = pos_s - pos_c;

	vecto.x = dir_c.y * diff.z - dir_c.z * diff.y;
	vecto.y = dir_c.z * diff.x - dir_c.x * diff.z;
	vecto.z = dir_c.x * diff.y - dir_c.y * diff.x;
	dist = dist(vecto) / dist(dir_c);
	return (dist);
}

float3	get_sphere_normale(float3 pos_s, float3 pos_c, float3 dir_c, float dist)
{
	// on prolonge le vecteur directeur par la distance
	// on ajoute a la position de la camera			=>	on a le point d'intersection.
	//	on lui soustrait la position de la sphere 	=>	on a la dorection	
}


/*
	dist = norme(dir vectoriel diff) / norme(dir_c);

	vecto.x = dir_c.y * diff.z - dir_c.z * diff.y;
	vecto.y = dir_c.z * diff.x - dir_c.x * diff.z;
	vecto.z = dir_c.x * diff.y - dir_c.y * diff.x;
*/

float	dist_sphere_cam(float3 diff, float3 dir)
{
	float	dist;
	float	dist2;
	float	a;
	float	b;
	float	c;
	float	delta;

	a = dot(dir, dir);
	b = 2 * dot(dir, diff);
	c = dot(diff, diff);
	delta = b * b - 4 a * c;
	if (delta < 0)
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


