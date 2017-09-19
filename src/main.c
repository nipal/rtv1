/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:48:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/18 17:58:37 by fjanoty          ###   ########.fr       */
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


int	main()
{
	t_env		e;

	get_env(&e);
	e.mlx = mlx_init();
	e.scene.env = &e;
	win_mlx_init(&e.scene, SCENE_X, SCENE_Y, "scene");
	init_win_event(&e.scene);
	mlx_start(&e);
	return (0);
}