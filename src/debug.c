/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:57:35 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/29 20:43:02 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void	init_ray(t_item *item, t_vec3 *dir, t_vec3 *dx, t_vec3 *dy);
void	find_collision(t_zbuff *zbuff, t_item *item, t_vec3 ray_dir);
int		get_phong_color(t_item *item, t_zbuff *zbuff, t_vec3 ray_dir);

int		debug_ray = 0;

void	test_ray(t_mlx_win *w, t_item *item, int i, int j)
{
	t_vec3	tmp_x;
	t_vec3	tmp_y;
	t_vec3	dir;
	t_vec3	dir_nrm;
	t_vec3	dx;
	t_vec3	dy;

	debug_ray = 1;
	printf("\n\n\n\n\n\n\n\n\n\n\n\ntest_ray:{%d, %d}\n", i, j);
	init_ray(item, &dir, &dx, &dy);
	tmp_x = vec3_scalar(dx, i);
	tmp_y = vec3_scalar(dy, j);
	dir = vec3_add3(dir, tmp_x, tmp_y);
	dir_nrm = vec3_normalise(dir);
	find_collision(w->z_buff + i + j * w->size_x, item, dir_nrm);
	w->data[i + j * w->size_x].nb = get_phong_color(item, w->z_buff + i + j * w->size_x, dir_nrm);

	debug_ray = 0;
}
