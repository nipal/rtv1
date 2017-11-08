/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:15:28 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 05:23:02 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

long		get_cam_offset(int id_cam)
{
	t_cam c;

	if (id_cam == 0)
		return ((long)(&c.pos) - (long)(&c));
	if (id_cam == 1)
		return ((long)(&c.uz) - (long)(&c));
	return (-1);
}

void		cam_finish(t_cam *cam, int comp)
{
	if (!cam)
		return ;
	if (!(comp & 1))
		cam->pos = vec3_set(0, 0, -15);
	if (!(comp & 2))
		cam->uz = vec3_set(0, 0, 1);
	if (!(comp & 4))
		cam->uy = vec3_set(0, 1, 0);
}

void		cam_comp_fill(char *str, int *add_curs, t_cam *cam, int id_comp)
{
	int		i;
	int		err;

	i = 0;
	(*(t_vec3*)((long)cam + (long)get_cam_offset(id_comp))) =
		str_get_vec3(str, &i, &err);
	*add_curs += i;
}

t_cam		*get_cam(char *str, int id, int *add_curs)
{
	t_cam	*cam;
	int		size;
	int		id_comp;
	int		i;
	int		comp;

	(void)id;
	if (!add_curs || !(cam = (t_cam*)malloc(sizeof(t_cam))))
		return (NULL);
	size = find_char_force(str, '}');
	i = 0;
	comp = 0;
	while (i < size - 1)
	{
		if ((id_comp = find_id_from_name(str + i, &i, CAM_COMP)) >= 0)
		{
			comp |= 1 << id_comp;
			cam_comp_fill(str + i, &i, cam, id_comp);
		}
	}
	*add_curs += size;
	cam_finish(cam, comp);
	return (cam);
}
