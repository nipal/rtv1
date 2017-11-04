/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 23:36:11 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 14:22:29 by fjanoty          ###   ########.fr       */
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

/*
**	Il manque une fonction de liste qui prenne en parametre un pointeur sur
**	fonction pour detruire les objet stoquer...
*/
