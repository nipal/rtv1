/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:14:53 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 05:42:19 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

long		get_light_offset(int id_light)
{
	t_light l;

	if (id_light == 0)
		return ((long)(&l.pos) - (long)(&l));
	if (id_light == 1)
		return ((long)(&l.col) - (long)(&l));
	return (-1);
}

void		light_finish(t_light *light, int comp)
{
	if (!light)
		return ;
	if (!(comp & 1))
		light->pos = vec3_set(0, 0, 0);
	if (!(comp & 2))
		light->col = vec3_set(255, 255, 255);
	color_range(&light->col);
}

void		light_comp_fill(char *str, int *add_curs, t_light *light
		, int id_comp)
{
	int		i;
	int		err;

	i = 0;
	(*(t_vec3*)((long)light + (long)get_light_offset(id_comp))) =
		str_get_vec3(str, &i, &err);
	*add_curs += i;
}

t_light		*get_light(char *str, int id, int *add_curs)
{
	t_light	*light;
	int		size;
	int		id_comp;
	int		i;
	int		comp;

	(void)id;
	if (!add_curs || !(light = (t_light*)malloc(sizeof(t_light))))
		return (NULL);
	size = find_char_force(str, '}');
	i = 0;
	comp = 0;
	while (i < size - 1)
	{
		if ((id_comp = find_id_from_name(str + i, &i, LIGHT_COMP)) >= 0)
		{
			comp |= 1 << id_comp;
			light_comp_fill(str + i, &i, light, id_comp);
		}
	}
	*add_curs += size;
	light_finish(light, comp);
	return (light);
}
