/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entities_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:19:12 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 05:26:48 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		entities_push(t_entities **beg, t_entities *new_elem)
{
	if (!beg || !new_elem)
		return ;
	new_elem->next = *beg;
	*beg = new_elem;
}

t_entities	*entities_create(void *data, int id)
{
	t_entities	*new_elem;

	if (!data || !(new_elem = (t_entities*)malloc(sizeof(t_entities))))
	{
		return (NULL);
	}
	if (id >= 0 && id <= 3)
	{
		new_elem->type = 0;
		new_elem->sub_type = id;
	}
	else
	{
		new_elem->type = (id == 4) ? 1 : 2;
		new_elem->sub_type = 0;
	}
	new_elem->entities = data;
	new_elem->next = NULL;
	return (new_elem);
}

void		entities_destroy(t_entities *elem)
{
	t_entities *tmp;

	while (elem)
	{
		tmp = elem->next;
		free(elem);
		elem = tmp;
	}
}
