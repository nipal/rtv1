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
