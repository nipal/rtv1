/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:26:28 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/03 23:36:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


/*
**	On va peuetre aussi metre une camera dedans
**	en gros c'est la structure qui serra initialiser avec le parsing
*/

void	TEMP_set_obj_nb(t_item *item)
{
	int	i;

	i = 0;
	while (item->obj[i].type >= 0)
		i++;
	item->nb_obj = i;
}


const	char	*obj_get_type_name(int id)
{
	switch (id)
	{
		case 0:
			return ("plan");
		case 1:
			return ("sphere");
		case 2:
			return ("cylinder");
		case 3:
			return ("cone");
	};
	return ("--noting--");
}

//void	obj_describe(t_obj *obj)
//{
//	ft_putstr(obj_get_type_name(obj->type));
//	ft_putstr("\n{\n");
//	vec3_print_str(obj->pos, "	pos	");
//	vec3_print_str(obj->dir, "	dir	");
//	vec3_print_str(obj->col, "	col	");
//	printf("	value	%f\n", obj->value);
//	printf("}\n\n");
//}

void	cam_describe2(t_cam *cam)
{
	ft_putstr("camera\n");
	ft_putstr("{\n");
	vec3_print_str(cam->pos, "	pos");
	vec3_print_str(cam->uz, "	dir");
	vec3_print_str(cam->uy, "	up");
//	printf("	pos	%f, %f, %f\n", cam->pos.x, cam->pos.y, cam->pos.z);
//	printf("	dir	%f, %f, %f\n", cam->uz.x, cam->uz.y, cam->uz.z);
//	printf("	up	%f, %f, %f\n", cam->uy.x, cam->uy.y, cam->uy.z);
	ft_putstr("}\n\n");
}

//void	light_describe(t_light *light)
//{
//	printf("light\n");
//	printf("{\n");
//	vec3_print_str(light->pos, "	pos	");
//	vec3_print_str(light->col, "	col	");
//	printf("}\n\n");
//}

//void	item_describe(t_item *item)
//{
//	int	i;
//	printf("obj:%d	light:%d	cam:%d\n\n", item->nb_obj, item->nb_light, item->nb_cam);
//	i = 0;
//	while (i < item->nb_obj)
//		obj_describe(item->obj + i++);
//	i = 0;
//	while (i < item->nb_light)
//		light_describe(item->light + i++);
//	i = 0;
//	while (i < item->nb_cam)
//		cam_describe2(item->cam + i++);
//}

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
//printf("\n===========================================\n");
//	item_describe(item);
//	old_item_init(item, w);
}

void	item_destroy(t_item *it)
{
	if (!it)
		return ;
	if (it->light)
		free(it->light);
	if (it->obj)
		free(it->obj);
	if (it->cam)
		free(it->cam);
}
