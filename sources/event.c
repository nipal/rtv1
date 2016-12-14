/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:14:03 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/14 17:03:37 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int		press_key(int key_code, t_win *w)
{
	printf("key:%d\n", key_code);
	if (key_code == 53)
		ft_exit(w->e);
	(void)w;
	return (key_code + 1);
}

int		release_key(int key_code, t_win *w)
{
	printf("key:%d\n", key_code);
	(void)w;
	return (key_code + 1);
}

int		motion_cursor(int x, int y, t_win *w)
{	
	printf("cursor:%d\n", (x + y));
	(void)w;
	return (x + y);
}

int		press_cursor(int button, int x, int y, t_win *w)
{
	printf("button:%d\n", button);
	(void)w;
	return (button + x + y);
}

int		release_cursor(int button, int x, int y, t_win *w)
{
	printf("button:%d\n", button);
	(void)w;
	return (button + x + y);
}
