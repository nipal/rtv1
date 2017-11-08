/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:23:41 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:25:16 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cam_go_front(t_cam *cam, double dist)
{
	cam->pos = vec3_add(cam->pos, vec3_scalar(cam->uz, dist));
}

void	cam_go_back(t_cam *cam, double dist)
{
	cam->pos = vec3_add(cam->pos, vec3_scalar(cam->uz, -dist));
}

void	cam_go_left(t_cam *cam, double dist)
{
	cam->pos = vec3_add(cam->pos, vec3_scalar(cam->ux, -dist));
}

void	cam_go_right(t_cam *cam, double dist)
{
	cam->pos = vec3_add(cam->pos, vec3_scalar(cam->ux, dist));
}
