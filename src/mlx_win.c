/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:47:38 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 14:24:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <mlx.h>

int			mlx_win_is_inside(t_mlx_win *w, int x, int y)
{
	return (x >= 0 && y >= 0 && x < w->size_x && y < w->size_y);
}

int			mlx_win_init(t_mlx_win *w, int size_x, int size_y, char *name)
{
	t_env	*e;

	e = get_env(NULL);
	ft_bzero(&e->scene, sizeof(t_mlx_win));
	e->scene.refresh = 1;
	if (!name)
		name = "new w";
	if (!(size_x > 0 && size_y > 0) || !w
			|| !(w->win = mlx_new_window(e->mlx, size_x, size_y, name))
			|| !(w->img = mlx_new_image(e->mlx, size_x, size_y))
			|| !(w->data = (t_pix*)mlx_get_data_addr(w->img, &(w->depth)
					, &(w->size_x), &(w->endian)))
			|| !(w->zbuff = (t_zbuff*)malloc(sizeof(t_zbuff) *
					size_x * size_y)))
		return (-1);
	w->name = name;
	w->mouse = vec3_set(0, 0, 0);
	w->prev_mouse = vec3_set(0, 0, 0);
	w->size_x = size_x;
	w->size_y = size_y;
	return (0);
}

void		init_win_event(t_mlx_win *w)
{
	mlx_hook(w->win, KEY_PRESS, (1 << 24) - 1, key_press, w);
	mlx_hook(w->win, KEY_RELEASE, (1 << 24) - 1, key_release, w);
	mlx_hook(w->win, BUTTON_PRESS, (1 << 24) - 1, mousse_press, w);
	mlx_hook(w->win, BUTTON_RELEASE, (1 << 24) - 1, mousse_release, w);
	mlx_hook(w->win, MOTION_NOTIFY, (1 << 24) - 1, mousse_motion, w);
}

void		mlx_win_finish(t_mlx_win *w)
{
	free(w->zbuff);
}

void		mlx_start(t_env *e)
{
	mlx_loop_hook(e->mlx, main_bcl, e);
	mlx_loop(e->mlx);
	mlx_do_sync(e->mlx);
}
