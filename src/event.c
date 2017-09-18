/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:22:06 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/18 18:05:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int		key_press(int key_code, t_mlx_win *w)
{
	printf("key_press:%d\n", key_code);
	(key_code == 53) ? rtv1_exit(w->env): (void)w;
	return (0);
}

int		key_release(int key_code, t_mlx_win *w)
{
	(void)w;
	printf("key_release:%d\n", key_code);
	return (0);
}

int		mousse_press(int button, int x, int y, t_mlx_win *w)
{
	(void)w;
	printf("mousse_press:%d	{%d, %d}\n", button, x, y);
	return (0);
}

int		mousse_release(int button, int x, int y, t_mlx_win *w)
{
	(void)w;
	printf("mousse_release:%d	{%d, %d}\n", button, x, y);
	return (0);
}

int		mousse_motion(int x, int y, t_mlx_win *w)
{
	(void)w;
	printf("mouse_motion:	{%d, %d}\n", x, y);
	return (0);
}

int		main_bcl(t_env *e)
{
	(void)e;
	
	return (0);
}
