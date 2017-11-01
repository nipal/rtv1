/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:43:43 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 02:21:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rtv1_exit(t_env *e)
{
	(void)e;
	if (e)
	{
		mlx_win_finish(&e->scene);
		lst_destroy_all(&e->item.all_segment);
		item_destroy(&e->item);
	}
	exit(0);
}
