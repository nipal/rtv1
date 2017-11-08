/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rtv1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 18:28:09 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:13:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		remove_coment(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
		{
			j = 0;
			while (str[i + j] && str[i + j] != '\n')
				j++;
			ft_memmove(str + i, str + i + j, ft_strlen(str + i + j) + 1);
		}
		i++;
	}
}

void		color_range(t_vec3 *col)
{
	if (col->x < 0)
		col->x = 0;
	if (col->y < 0)
		col->y = 0;
	if (col->z < 0)
		col->z = 0;
	if (col->x > 255)
		col->x = 255;
	if (col->y > 255)
		col->y = 255;
	if (col->z > 255)
		col->z = 255;
}

void		parse_error(int id, char *str)
{
	ft_putstr("parse error	");
	ft_putnbr(id);
	ft_putstr(":	txt==>");
	ft_putstr(str);
	ft_putstr("<==\n");
	exit(0);
}

t_entities	*get_entities(char *file_str)
{
	int			i;
	int			id;
	t_entities	*beg;
	t_entities	*node;

	beg = NULL;
	remove_coment(file_str);
	i = 0;
	while (!is_parsing_finnished(file_str + i))
	{
		if ((id = find_id_from_name(file_str + i, &i, OBJ_TYPE)) < 0)
			parse_error(-1, "no obj_name found");
		if ((i += find_char(file_str + i, '{')) < 0)
			parse_error(-2, "no begin obj found");
		if (id <= 3)
			node = entities_create(get_assets(file_str + i, id, &i), id);
		else if (id == 4)
			node = entities_create(get_light(file_str + i, id, &i), id);
		else if (id == 5)
			node = entities_create(get_cam(file_str + i, id, &i), id);
		entities_push(&beg, node);
	}
	return (beg);
}

int			item_obj_alloc(t_entities *node, t_item *item)
{
	if (!node || !item)
		return (0);
	item->nb_light = 0;
	item->nb_obj = 0;
	item->nb_cam = 0;
	while (node)
	{
		if (node->type == 0)
			item->nb_obj++;
		else if (node->type == 1)
			item->nb_light++;
		else if (node->type == 2)
			item->nb_cam++;
		node = node->next;
	}
	if (!(item->obj = (t_obj*)malloc(sizeof(t_obj) * item->nb_obj))
		|| !(item->light = (t_light*)malloc(sizeof(t_light) * item->nb_light))
		|| !(item->cam = (t_cam*)malloc(sizeof(t_cam) * item->nb_cam)))
		return (0);
	return (1);
}
