/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:21:49 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/21 00:26:26 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	test_init_obj(t_obj *obj)
{
	ft_bzero(obj, sizeof(obj) * 5);
	obj[0].type = 1;
	obj[0].radius = 4;
	vec_set(obj->ang, 0, 0, 0);
	vec_set(obj->pos, 0, 5, 0);
	vec_set(obj->dir, 0, 1, 0);

	obj[1].type = -1;
}


void	test_basique(t_env *e)
{
	t_obj	obj[5];
	(void)e;
	(void)obj;

	test_init_obj(obj);

	fill_zbuff(e, &e->scene, &e->cam, obj);
	color_scene(&e->scene, obj); 
	mlx_put_image_to_window(e->mlx, e->scene.win, e->scene.img, 0, 0);
	mlx_do_sync(e->mlx);
}
