/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:16:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/09 09:37:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

long		get_asset_offset(int id_assets)
{
	t_obj o;

	if (id_assets == 0)
		return ((long)&o.value - (long)(&o));
	if (id_assets == 1)
		return ((long)&o.pos - (long)(&o));
	if (id_assets == 2)
		return ((long)&o.dir - (long)(&o));
	if (id_assets == 3)
		return ((long)&o.col - (long)(&o));
	if (id_assets == 4)
		return ((long)&o.pow_spec - (long)(&o));
	return (-1);
}

void		item_finish_plan(t_obj *plan)
{
	if (vec3_norme((plan->dir = vec3_normalise(plan->dir))) != 1)
		plan->dir = vec3_set(0, 1, 0);
	plan->value = -vec3_dot(plan->dir, plan->pos);
}

void		asset_comp_fill(char *str, int *add_curs, t_obj *obj, int id_comp)
{
	int		i;
	int		err;

	i = 0;
	if (id_comp == 0 || id_comp == 4)
		(*(double*)((long)obj + (long)get_asset_offset(id_comp))) =
			str_get_double(str, &i);
	else
		(*(t_vec3*)((long)obj + (long)get_asset_offset(id_comp))) =
			str_get_vec3(str, &i, &err);
	*add_curs += i;
}

void		asset_finish(t_obj *obj, int comp)
{
	double	coef;

	if (!(comp & 1))
		obj->value = 1;
	if (!(comp & 2))
		obj->pos = vec3_set(0, 0, 0);
	if (!(comp & 4))
		obj->dir = vec3_normalise(vec3_set(1, -1, -1));
	if (!(comp & 8))
		obj->col = vec3_set(200, 200, 200);
	if (!(comp & 8))
		obj->pow_spec = 0;
	color_range(&obj->col);
	if (obj->type == CONE)
	{
		coef = tan(obj->value * M_PI / 180.0);
		obj->value = coef * coef;
	}
	else
		obj->value = fabs(obj->value);
	if (obj->type == PLAN)
		item_finish_plan(obj);
}

t_obj		*get_assets(char *str, int id, int *add_curs)
{
	t_obj	*obj;
	int		size;
	int		id_comp;
	int		i;
	int		comp;

	if (!add_curs || !(obj = (t_obj*)malloc(sizeof(t_obj))))
		return (NULL);
	size = find_char_force(str, '}');
	i = 0;
	comp = 0;
	obj->type = id;
	id_comp = -1;
	while (i < size - 1)
	{
		if ((id_comp = find_id_from_name(str + i, &i, ASSETS_COMP)) >= 0)
		{
			comp |= 1 << id_comp;
			asset_comp_fill(str + i, &i, obj, id_comp);
		}
	}
	*add_curs += size;
	asset_finish(obj, comp);
	return (obj);
}
