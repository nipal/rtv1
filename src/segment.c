/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 00:48:56 by fjanoty           #+#    #+#             */
/*   Updated: 2018/02/17 18:17:14 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_seg	seg_set(t_vec3 from, t_vec3 to, t_vec3 c1, t_vec3 c2)
{
	t_seg	seg;

	seg.from = from;
	seg.to = to;
	seg.c1 = c1;
	seg.c2 = c2;
	return (seg);
}

t_seg	*seg_create(t_vec3 from, t_vec3 to, t_vec3 c1, t_vec3 c2)
{
	t_seg	*seg;

	if (!(seg = (t_seg*)malloc(sizeof(t_seg))))
		return (NULL);
	*seg = seg_set(from, to, c1, c2);
	return (seg);
}

void	seg_add_obj_nrm(t_lst **beg, t_mlx_win *w, int x, int y)
{
	int		id;
	t_seg	s;

	id = x + y * w->size_x;
	if (mlx_win_is_inside(w, x, y) && w->zbuff[id].id >= 0)
	{
		s.from = vec3_add(w->zbuff[id].pos, vec3_scalar(w->zbuff[id].nrm, -1));
		s.to = vec3_add(s.from, vec3_scalar(w->zbuff[id].nrm, 2));
		s.c1 = vec3_scalar(vec3_add_scalar(w->zbuff[id].nrm, 1.0), 255.0 / 2.0);
		s.c2 = vec3_set(200, 200, 200);
		lst_add_front(beg, lst_create_node_copy(&s, sizeof(t_seg)));
	}
}

void	seg_add_ray_light(t_lst **beg, t_mlx_win *w, int x, int y)
{
	int		id;
	int		i;
	t_seg	s;
	t_light	*light;
	int		nb_light;

	nb_light = w->env->item.nb_light;
	light = w->env->item.light;
	i = 0;
	while (i < nb_light)
	{
		id = x + y * w->size_x;
		if (mlx_win_is_inside(w, x, y) && w->zbuff[id].id >= 0)
		{
			s.from = w->zbuff[id].pos;
			s.to = light[i].pos;
			s.c1 = light[i].col;
			s.c2 = vec3_set(200, 200, 200);
			lst_add_front(beg, lst_create_node_copy(&s, sizeof(t_seg)));
		}
		i++;
	}
}

void	seg_print(void *env, void *data)
{
	t_mlx_win	*w;
	t_seg		*seg;

	w = (t_mlx_win*)env;
	seg = (t_seg*)data;
	pp_draw_segment(w, seg->from, seg->to, seg->c1);
}
