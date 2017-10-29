/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:22:06 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/29 19:52:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>


/*
**	
*/

// TODO pointeur sur fonction pour les touche, il fuadra juste faire un truc pour les
// 		touche linux (max = 2^16 -1)
int		key_press(int key_code, t_mlx_win *w)
{
	(void)key_code;
	double	ang = 5;
	double	dist = 0.5;
	
//	printf("key_press:%d\n", key_code);	
	(key_code == KEY_ESC) ? rtv1_exit(w->env), w->refresh = 1: (void)w;
	(key_code == KEY_A) ? cam_turn_left(w->cam, ang * DEG), w->refresh = 1: (void)w;
	(key_code == KEY_D) ? cam_turn_right(w->cam, ang * DEG), w->refresh = 1: (void)w;
	(key_code == KEY_S) ? cam_turn_down(w->cam, ang * DEG), w->refresh = 1: (void)w;
	(key_code == KEY_W) ? cam_turn_up(w->cam, ang * DEG), w->refresh = 1: (void)w;
	(key_code == KEY_H) ? cam_go_left(w->cam, dist) , w->refresh = 1: (void)w;
	(key_code == KEY_L) ? cam_go_right(w->cam, dist) , w->refresh = 1: (void)w;
	(key_code == KEY_J) ? cam_go_back(w->cam, dist) , w->refresh = 1: (void)w;
	(key_code == KEY_K) ? cam_go_front(w->cam, dist) , w->refresh = 1: (void)w;
	(key_code == KEY_P) ? cam_describe2(w->cam) : (void)w;
	(key_code == KEY_O) ? obj_describe(w->env->item.obj) : (void)w;
	(key_code == KEY_I) ? light_describe(w->env->item.light) : (void)w;
//	mlx_put_image_to_window(w->env->mlx, w->env->scene.win, w->env->scene.img, 0, 0);
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
	if (button == 1)
		test_ray(w, &w->env->item, x, y);
//	printf("mousse_press:%d	{%d, %d}\n", button, x, y);
	return (0);
}

int		mousse_release(int button, int x, int y, t_mlx_win *w)
{
	(void)w;(void)x;(void)y;(void)button;
//	printf("mousse_release:%d	{%d, %d}\n", button, x, y);
	return (0);
}

int		mousse_motion(int x, int y, t_mlx_win *w)
{
	(void)w;(void)x;(void)y;
//	printf("mouse_motion:	{%d, %d}\n", x, y);
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

void	print_time(long *histo, int size, int beg)
{
	int	i;
	int	j;

	i = beg % size;
	j = 0;
	printf("========\n");
	while (j < size)
	{
//		if (j == beg)
//			printf("-->");
		printf("[%d]:%ld\n", j, histo[i]);
		i = (i + 1) % size;
		j++;
	}


}

void	actual_time(t_env *e)
{
	(void)e;
	/*
	t_time	t;
	static	int	i = 0;
	static	long long	histo[30];
	const	int		histo_size = (sizeof(histo) / sizeof(long));
	
	gettimeofday(&t, NULL);
	e->last_frame = e->frame;
	e->frame = (long)t.tv_usec + ((t.tv_sec % (3600))) * 1000000;
//	printf("fps:%.1f\n", (1.0 / ((double)(e->frame - e->last_frame) / 1000000.0)));
	if ((e->frame / 1000000) - (e->last_frame / 1000000) != 0)
	{
//		printf("[%ld][%ld]================\n", (e->frame / 1000000), (e->last_frame / 1000000));
	}
//	printf("time %ld\n", (e->frame - e->last_frame));
	histo[i] = e->frame;
	print_time(histo, histo_size, i + 1);
//	printf("%d\n1000000\n", t.tv_usec);
//	printf("i:%d\n", i);
	long diff = (histo[i] - histo[(i - 1) % histo_size];
	printf("FPS:	%.1f\n", ((1.0 / (double)((histo[i] - histo[(i - 1) % histo_size]) / 1000000.0))));
	if (++i >= histo_size)
		i = 0;
		*/
}

int		main_bcl(t_env *e)
{
	(void)e;

	if (1 || e->scene.refresh)	
	{
		e->scene.refresh = 0;
		launch_ray(&e->scene, &e->item);
		mlx_put_image_to_window(e->mlx, e->scene.win, e->scene.img, 0, 0);
	}
	actual_time(e);
//	test_put_pixel(&e->scene);
	test_basique(e);
	mlx_put_image_to_window(e->mlx, e->scene.win, e->scene.img, 0, 0);
	
	return (0);
}
