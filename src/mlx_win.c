/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:47:38 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/15 01:42:54 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>

/*suppresion de size_ine dans la structure win_mlx*/

int			*win_mlx_init(t_win_mlx *w, int size_x, int size_y, char *name)
{
	if (!name)
		name = "new w";
	if (!e || !(size_x > 0 && size_y > 0 || !w)
			|| !(w->win = mlx_new_window(e->mlx, size_x, size_y, name))
			|| !(w->img = mlx_new_image(e->mlx, size_x, size_y))
			|| !(w->data = (t_pix*)mlx_get_data_addr(w->img, &(w->depth)
					, &(w->size_x), &(w->endian)))
		return (-1);
	w->name = name;
	vec3_init(w->mouse, 0, 0, 0);
	vec3_init(w->prev_mouse, 0, 0, 0);
	w->size_x = size_x;
	w->size_y = size_y;
	return (0);
}


// il faudra encore un pe trier de truc
void		init_win_event(t_win *w, t_env *e)
{
	(void)e;

	mlx_hook(w->win, KEY_PRESS, (1 << 24) - 1, press_key, w);
	mlx_hook(w->win, KEY_RELEASE, (1 << 24) - 1, release_key, w);
	mlx_hook(w->win, BUTTON_PRESS, (1 << 24) - 1, press_button, w);
	mlx_hook(w->win, BUTTON_RELEASE, (1 << 24) - 1, release_button, w);
	mlx_hook(w->win, MOTION_NOTIFY, (1 << 24) - 1, motion_cursor, w);
}
////////////// pck voila

void		win_mlx_finish()
{
			/*	les evenltuel fonction de fin de la mlx	*/
			/*	mais bon voila	*/
}

void	start_mlx()
{
	
	mlx_loop_hook(e->mlx, main_work, e);
	mlx_loop(e->mlx);
	mlx_do_sync(e->mlx);
}
