/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:26:28 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:27:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*obj_get_type_name(int id)
{
	if (id == 0)
		return ("plan");
	if (id == 1)
		return ("sphere");
	if (id == 2)
		return ("cylinder");
	if (id == 3)
		return ("cone");
	return ("--noting--");
}

void	cam_describe2(t_cam *cam)
{
	ft_putstr("camera\n");
	ft_putstr("{\n");
	vec3_print_str(cam->pos, "	pos");
	vec3_print_str(cam->uz, "	dir");
	vec3_print_str(cam->uy, "	up");
	ft_putstr("}\n\n");
}

void	init_obj_func(t_item *item)
{
	item->obj_dist_all[0] = dist_all_plan;
	item->obj_dist_all[1] = dist_all_sphere;
	item->obj_dist_all[2] = dist_all_cylinder;
	item->obj_dist_all[3] = dist_all_cone;
	item->obj_dist[0] = get_dist_plan;
	item->obj_dist[1] = get_dist_sphere;
	item->obj_dist[2] = get_dist_cylinder;
	item->obj_dist[3] = get_dist_cone;
	item->obj_nrm[0] = get_normal_plan;
	item->obj_nrm[1] = get_normal_sphere;
	item->obj_nrm[2] = get_normal_cylinder;
	item->obj_nrm[3] = get_normal_cone;
}

void	add_cam_and_light_if_not(t_item *item, t_mlx_win *w)
{
	if (item->nb_cam <= 0)
	{
		if (!(item->cam = (t_cam*)malloc(sizeof(t_cam))))
			rtv1_exit(get_env(NULL));
		item->cam->pos = vec3_set(0, 0, -5);
		item->cam->uz = vec3_set(0, 0, 1);
		item->cam->uy = vec3_set(0, 1, 0);
		item->cam->ux = vec3_set(1, 0, 0);
		item->nb_cam = 1;
		w->cam = item->cam;
	}
	if (item->nb_light <= 0)
	{
		if (!(item->light = (t_light*)malloc(sizeof(t_light))))
			rtv1_exit(get_env(NULL));
		if (item->nb_obj > 0)
			item->light->pos = vec3_add(item->obj->pos, vec3_set(0, 0, 1));
		else
			item->light->pos = vec3_set(0, 0, 0);
		item->light->col = vec3_set(255, 255, 255);
		item->nb_light = 1;
	}
	item->all_cam = item->cam;
}

void	item_init(t_item *item, t_mlx_win *w, const char *file_path)
{
	int			file_size;
	char		*file_str;
	t_entities	*lst;

	if (!(file_str = file_get_str(file_path, &file_size)))
		rtv1_exit(get_env(NULL));
	if (!(lst = get_entities(file_str)))
		rtv1_exit(get_env(NULL));
	if (!(item_obj_alloc(lst, item)))
		rtv1_exit(get_env(NULL));
	item_fill(lst, item);
	entities_destroy(lst);
	item->size_x = w->size_x;
	item->size_y = w->size_y;
	free(file_str);
	init_obj_func(item);
	w->cam = item->cam;
	item->all_segment = NULL;
	add_cam_and_light_if_not(item, w);
	item->id_cam = 0;
}
