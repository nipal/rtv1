/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:22:06 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/26 16:03:37 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>


/*
**	
*/

int		key_press(int key_code, t_mlx_win *w)
{
	(void)key_code;
	
//	printf("key_press:%d\n", key_code);	
	(key_code == 53) ? rtv1_exit(w->env) : (void)w;
	(key_code == KEY_LEFT) ? cam_turn_left(&w->cam, 1.0 * (2.0 * M_PI / 360.0)) : (void)w;
	(key_code == KEY_RIGHT) ? cam_turn_right(&w->cam, 1.0 * (2.0 * M_PI / 360.0)) : (void)w;
	(key_code == KEY_DOWN) ? cam_turn_down(&w->cam, 1.0 * (2.0 * M_PI / 360.0)) : (void)w;
	(key_code == KEY_UP) ? cam_turn_up(&w->cam, 1.0 * (2.0 * M_PI / 360.0)) : (void)w;
	return (0);
}

int		key_release(int key_code, t_mlx_win *w)
{
	(void)w;
	(void)key_code;
//	printf("key_release:%d\n", key_code);
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

void	test_put_pixel(t_mlx_win *win)
{
	int	i;
	int	j;

	j = 0;
	while (j < win->size_y)
	{
		i = 0;
		while (i < win->size_x)
		{
			win->data[i + win->size_x * j].comp[0] = 10;
			win->data[i + win->size_x * j].comp[1] = 40;
			win->data[i + win->size_x * j].comp[2] = 3;
			win->data[i + win->size_x * j].comp[3] = 0;
			i++;
		}
		j++;
	}
}

int		main_bcl(t_env *e)
{
	(void)e;
	
//	test_put_pixel(&e->scene);
	test_basique(e);
	mlx_put_image_to_window(e->mlx, e->scene.win, e->scene.img, 0, 0);
	
	return (0);
}
