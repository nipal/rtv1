/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:47:38 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/27 17:59:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "vec_math.h"
#include "libft.h"
#include <mlx.h>

/*suppresion de size_ine dans la structure win_mlx*/

int			mlx_win_init(t_mlx_win *w, int size_x, int size_y, char *name)
{
	t_env	*e;

	e = get_env(NULL);
	ft_bzero(&e->scene, sizeof(t_mlx_win));
	if (!name)
		name = "new w";
	if (!(size_x > 0 && size_y > 0) || !w
			|| !(w->win = mlx_new_window(e->mlx, size_x, size_y, name))
			|| !(w->img = mlx_new_image(e->mlx, size_x, size_y))
			|| !(w->data = (t_pix*)mlx_get_data_addr(w->img, &(w->depth)
					, &(w->size_x), &(w->endian)))
			|| !(w->z_buff = (t_zbuff*)malloc(sizeof(t_zbuff) * size_x * size_y)))
		return (-1);
	w->name = name;
	vec3_init(w->mouse, 0, 0, 0);
	vec3_init(w->prev_mouse, 0, 0, 0);
	w->size_x = size_x;
	w->size_y = size_y;
	return (0);
}

// il faudra encore un pe trier de truc
void		init_win_event(t_mlx_win *w)
{
	mlx_hook(w->win, KEY_PRESS, (1 << 24) - 1, key_press, w);
	mlx_hook(w->win, KEY_RELEASE, (1 << 24) - 1, key_release, w);
	mlx_hook(w->win, BUTTON_PRESS, (1 << 24) - 1, mousse_press, w);
	mlx_hook(w->win, BUTTON_RELEASE, (1 << 24) - 1, mousse_release, w);
	mlx_hook(w->win, MOTION_NOTIFY, (1 << 24) - 1, mousse_motion, w);
}
////////////// pck voila

void		mlx_win_finish(t_mlx_win *w)
{
	free(w->z_buff);
			/*	les evenltuel fonction de fin de la mlx	*/
			/*	mais bon voila	*/
}

void	mlx_start(t_env *e)
{
	mlx_loop_hook(e->mlx, main_bcl, e);
	mlx_loop(e->mlx);
	mlx_do_sync(e->mlx);
}
