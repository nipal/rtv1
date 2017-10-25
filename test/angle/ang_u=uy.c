/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ang_u=uy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:55:23 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/25 18:16:58 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "quaternion.h"

int	main()
{
	t_vec3	v1, v2, v3;

	v1 = vec3_set(0, 1, 0);
	v2 = vec3_cartesien_spherique(v1);
	vec3_print_str(v2, "ang");
	return (0);
}
