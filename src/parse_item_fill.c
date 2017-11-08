/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_item_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:12:07 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 05:59:00 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		obj_manage_rot(t_obj *obj)
{
	t_vec3	ang;

	ang = vec3_cartesien_spherique(obj->dir);
	obj->rot_inv = mat3_rot_all(-ang.x, -ang.y, 0);
}

void		item_fill_assets(t_entities *node, t_item *item)
{
	int		i;
	t_obj	obj;

	i = 0;
	while (node)
	{
		if (node->type == TYPE_ASSET)
		{
			obj = *((t_obj*)(node->entities));
			if ((float)vec3_norme((obj.dir = vec3_normalise(obj.dir))) != 1)
				obj.dir = vec3_set(0, 1, 0);
			if (node->sub_type == PLAN)
				obj.value = -vec3_dot(obj.dir, obj.pos);
			if (node->sub_type == CYLINDER || node->sub_type == CONE)
				obj_manage_rot(&obj);
			item->obj[i++] = obj;
		}
		node = node->next;
	}
}

void		item_fill_cam(t_entities *node, t_item *item)
{
	int		i;
	t_cam	cam;

	i = 0;
	while (node)
	{
		if (node->type == TYPE_CAM)
		{
			cam = *((t_cam*)(node->entities));
			if ((float)vec3_norme((cam.uz = vec3_normalise(cam.uz))) != 1)
				cam.uz = vec3_set(0, 0, 1);
			if (cam.uz.x == 0 && cam.uz.z == 0)
				cam.uy = vec3_set(0, 0, -1);
			else if (cam.uz.y == 0)
				cam.uy = vec3_set(0, 1, 0);
			else
				cam.uy = vec3_normalise(vec3_add(
	vec3_set(0, -vec3_dot(cam.uz, cam.uz) / cam.uz.y, 0), cam.uz));
			cam.ux = vec3_normalise(vec3_cross(cam.uy, cam.uz));
			item->cam[i++] = cam;
		}
		node = node->next;
	}
}

void		item_fill_light(t_entities *node, t_item *item)
{
	int	i;

	i = 0;
	while (node)
	{
		if (node->type == TYPE_LIGHT)
		{
			item->light[i++] = *((t_light*)(node->entities));
		}
		node = node->next;
	}
}

void		item_fill(t_entities *beg, t_item *item)
{
	item_fill_light(beg, item);
	item_fill_cam(beg, item);
	item_fill_assets(beg, item);
}
