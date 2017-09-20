/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:48:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/21 00:25:08 by fjanoty          ###   ########.fr       */
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

void	init_cam(t_basis *cam)
{
	cam_init_draw_func(get_env(NULL)); // need to init the pontiner on function
	basis_reset(cam);

}

void	init_rtv1()
{
}

int		main()
{
	t_env		e;
	ft_bzero(&e, sizeof(t_env));

	get_env(&e);
	e.mlx = mlx_init();
	e.scene.env = &e;
	win_mlx_init(&e.scene, SCENE_X, SCENE_Y, "scene");
	e.scene.env = &e; // il faudra mieux metre la camera dans la scene
	init_cam(&e.cam);

	init_win_event(&e.scene);
	mlx_start(&e);
	return (0);
}
