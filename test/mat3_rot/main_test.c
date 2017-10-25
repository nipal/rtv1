/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:22:16 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/25 15:37:35 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "../../quaternion/quaternion.h"

/*
 * On veux tester les matrice de rotation
*/

int	main()
{

	t_vec3	v1, v2, v3;
	t_mat3	rot_inv, mx, my, mz, m_id;

	v1 = vec3_normalise(vec3_set(-2, 4, 23)); 	// on lui donne une valeur
	v2 = vec3_cartesien_spherique(v1);			// on recupere ses angle

	// normalement les angles permete de revenir a {0, 0, 1} si on applique les rotation inverse
	rot_inv = mat3_rot_all(-v2.x, -v2.y, 0);
	v3 = mat3_mult_vec3(rot_inv, v1);

	vec3_print_str(v1, "v1:");
	vec3_print_str(v2, "v2:");
	vec3_print_str(v3, "v3:");

	mx = mat3_rot_x(0);
	my = mat3_rot_y(0);
	mz = mat3_rot_z(0);
	m_id = mat3_get_id();

	mat3_print_str(mx, "mx(0)");
	mat3_print_str(my, "my(0)");
	mat3_print_str(mz, "mz(0)");
	mat3_print_str(m_id, "m_id");
	return (0);
}
