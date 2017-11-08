/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 23:36:11 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:32:11 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_lst	*lst_create_node(void *ptr)
{
	t_lst	*node;

	if (!(node = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	node->cpy = 0;
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

t_lst	*lst_create_node_copy(void *ptr, size_t size)
{
	t_lst	*node;

	if (!(node = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	node->cpy = 1;
	if (!(node->ptr = malloc(size)))
		return (NULL);
	if (ptr)
		ft_memcpy(node->ptr, ptr, size);
	node->next = NULL;
	return (node);
}

void	lst_add_front(t_lst **beg, t_lst *node)
{
	if (!node)
	{
		perror("lst: nothging to add\n");
		return ;
	}
	node->next = *beg;
	*beg = node;
}

void	lst_add_back(t_lst **beg, t_lst *node)
{
	t_lst	*elem;

	elem = *beg;
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
		elem->next = node;
	}
	else
		*beg = node;
}
