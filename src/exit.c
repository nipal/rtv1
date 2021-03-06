/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:43:43 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:27:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	item_destroy(t_item *it)
{
	if (!it)
		return ;
	if (it->light)
		free(it->light);
	if (it->obj)
		free(it->obj);
	if (it->cam)
		free(it->all_cam);
}

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
