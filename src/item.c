/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:26:28 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/05 16:42:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


/*
**	On va peuetre aussi metre une camera dedans
**	en gros c'est la structure qui serra initialiser avec le parsing
*/

void	init_cam(t_basis *cam)
{
	cam_init_draw_func(get_env(NULL)); // need to init the pontiner on function
	basis_reset(cam);
	vec_set(cam->pos, 0, 0, -21);
}

void	TEMP_set_obj_nb(t_item *item)
{
	int	i;

	i = 0;
	while (item->obj[i].type >= 0)
		i++;
	item->nb_obj = i;
}

void	old_item_init(t_item *item, t_mlx_win *w)
{
	if (!item)
		rtv1_exit(get_env());
	ft_bzero(item, sizeof(item));
	if (!(item->obj = (t_obj*)malloc(sizeof(t_obj) * 5))
		|| !(item->light = (t_light*)malloc(sizeof(t_light) * 5)))
		rtv1_exit(get_env());
	item->nb_light = 4;
	item->nb_obj = 4;
	item->obj_dist[0] = get_dist_plan;
	item->obj_dist[1] = get_dist_sphere;
	item->obj_dist[2] = get_dist_cylinder;
	item->obj_dist[3] = get_dist_cone;
	item->obj_nrm[0] = set_normal_plan;
	item->obj_nrm[1] = set_normal_sphere;
	item->obj_nrm[2] = set_normal_cylinder;
	item->obj_nrm[3] = set_normal_cone;
	test_init_obj(item->obj);
	test_init_light(item->light, item->nb_light);
	item->size_x = w->size_x;
	item->size_y = w->size_y;
	item->cam = &w->cam;
	TEMP_set_obj_nb(item);

}

void	item_init(t_item *item, t_mlx_win *w, const char *file_path)
{
	(void)w;
	int		file_size;
	char	*str;

	if (!(str = file_str(file_path, &file_size)))
		rtv1_exit(get_env(NULL));
	rtv1_parse_file(str, file_size, item);
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
}
