/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:30:54 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:32:10 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	lst_map(t_lst *beg, void (*f)(void *))
{
	t_lst	*node;

	node = beg;
	while (node)
	{
		f(node->ptr);
		node = node->next;
	}
}

void	lst_map_env(t_lst *beg, void (*f)(void *env, void *ptr), void *env)
{
	t_lst	*node;

	node = beg;
	while (node)
	{
		f(env, node->ptr);
		node = node->next;
	}
}
