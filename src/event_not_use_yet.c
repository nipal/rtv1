/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_not_use_yet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:27:57 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:28:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_release(int key_code, t_mlx_win *w)
{
	(void)w;
	(void)key_code;
	return (0);
}

int		mousse_release(int button, int x, int y, t_mlx_win *w)
{
	(void)w;
	(void)x;
	(void)y;
	(void)button;
	return (0);
}

int		mousse_motion(int x, int y, t_mlx_win *w)
{
	(void)w;
	(void)x;
	(void)y;
	return (0);
}
