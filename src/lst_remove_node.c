/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_remove_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:30:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:32:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	lst_destroy_one(t_lst **node)
{
	if ((*node)->cpy)
		free((*node)->ptr);
	ft_bzero(*node, sizeof(t_lst));
	free(*node);
	*node = NULL;
}

void	lst_destroy_all(t_lst **beg)
{
	t_lst	*next;
	t_lst	*node;

	node = *beg;
	while (node)
	{
		next = node->next;
		lst_destroy_one(&node);
		node = next;
	}
}

void	lst_remove_node(t_lst **beg, t_lst *target)
{
	t_lst	*prev;
	t_lst	*node;

	node = *beg;
	prev = NULL;
	while (node)
	{
		if (node == target)
		{
			if (prev)
				prev->next = node->next;
			else
				*beg = node->next;
		}
		else
			prev = node;
		node = node->next;
	}
}

void	lst_remove_node_if(t_lst **beg, int (*f)(t_lst*))
{
	t_lst	*prev;
	t_lst	*node;

	node = *beg;
	prev = NULL;
	while (node)
	{
		if (f(node))
		{
			if (prev)
				prev->next = node->next;
			else
			{
				*beg = node->next;
				node = *beg;
				continue ;
			}
			node = prev->next;
			continue ;
		}
		prev = node;
		node = node->next;
	}
}

void	lst_remove_destroy_node_if(t_lst **beg, int (*f)(t_lst*))
{
	t_lst	*prev;
	t_lst	*node;

	node = *beg;
	prev = NULL;
	while (node)
	{
		if (f(node))
		{
			lst_destroy_one(&node);
			if (prev)
				prev->next = node->next;
			else
			{
				*beg = node->next;
				node = *beg;
				continue ;
			}
			node = prev->next;
			continue ;
		}
		prev = node;
		node = node->next;
	}
}
