/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:48:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/27 23:24:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <mlx.h>

t_env	*get_env(t_env *e)
{
	static	t_env	*env = NULL;

	if (e)
		env = e;
	return (env);
}


void	init_rtv1()
{
}

int		main()
{
	t_env		e;
	ft_bzero(&e, sizeof(t_env));


//	rotation_test();
//	/*
	get_env(&e);
	e.mlx = mlx_init();
	e.scene.env = &e;
	mlx_win_init(&e.scene, SCENE_X, SCENE_Y, "scene");
	e.scene.env = &e; // il faudra mieux metre la camera dans la scene
	init_cam(&e.scene.cam);
	item_init(&e.item, &e.scene);
	init_win_event(&e.scene);

	fill_zbuff(&e.scene, &e.item);
	mlx_put_image_to_window(e.mlx, e.scene.win, e.scene.img, 0, 0);

	mlx_start(&e);
//	*/
	return (0);
}
