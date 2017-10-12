/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:48:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/11 20:20:42 by fjanoty          ###   ########.fr       */
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

void	init_mlx_win(t_mlx_win *w)
{
	w->refresh = 1;
}

void	init_rtv1(t_env *e, const char *file_name)
{
	get_env(e);
	e->mlx = mlx_init();
	e->scene.env = e;
	mlx_win_init(&e->scene, SCENE_X, SCENE_Y, "scene");
	e->scene.env = e; // il faudra mieux metre la camera dans la scene
	item_init(&e->item, &e->scene, file_name);
	cam_init(e->scene.cam);
	init_win_event(&e->scene);

	mlx_start(e);
}

int		main(int ac, char **av)
{
	t_env		e;

	if (ac < 2)
	{
		printf("usage:	rtv1 SCENE_FILE_PATH\n");
		return (0);
	}
	ft_bzero(&e, sizeof(t_env));
	init_rtv1(&e, av[1]);
	return (0);
}
