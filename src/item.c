/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:26:28 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/29 21:26:33 by fjanoty          ###   ########.fr       */
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

void	item_init(t_item *it, t_mlx_win *w)
{
	if (!it)
		rtv1_exit(get_env());
	ft_bzero(it, sizeof(it));
	if (!(it->obj = (t_obj*)malloc(sizeof(t_obj) * 5))
		|| !(it->light = (t_light*)malloc(sizeof(t_light) * 5)))
		rtv1_exit(get_env());
	it->nb_light = 4;
	it->nb_obj = 4;
	it->obj_dist[0] = get_dist_plan;
	it->obj_dist[1] = get_dist_sphere;
	it->obj_dist[2] = get_dist_cylinder;
	it->obj_dist[3] = get_dist_cone;
	it->obj_nrm[0] = set_normal_plan;
	it->obj_nrm[1] = set_normal_sphere;
	it->obj_nrm[2] = set_normal_cylinder;
	it->obj_nrm[3] = set_normal_cone;
	test_init_obj(it->obj);
	test_init_light(it->light, it->nb_light);
	it->size_x = w->size_x;
	it->size_y = w->size_y;
	it->cam = &w->cam;
	TEMP_set_obj_nb(it);
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
