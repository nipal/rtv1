/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:24:31 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:25:18 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cam_turn_left(t_cam *cam, double ang)
{
	cam->ux = quaternion_rot(cam->ux, vec3_set(0, 1, 0), -ang);
	cam->uy = quaternion_rot(cam->uy, vec3_set(0, 1, 0), -ang);
	cam->uz = quaternion_rot(cam->uz, vec3_set(0, 1, 0), -ang);
}

void	cam_turn_right(t_cam *cam, double ang)
{
	cam->ux = quaternion_rot(cam->ux, vec3_set(0, 1, 0), ang);
	cam->uy = quaternion_rot(cam->uy, vec3_set(0, 1, 0), ang);
	cam->uz = quaternion_rot(cam->uz, vec3_set(0, 1, 0), ang);
}

void	cam_turn_down(t_cam *cam, double ang)
{
	cam->ux = quaternion_rot(cam->ux, cam->ux, -ang);
	cam->uy = quaternion_rot(cam->uy, cam->ux, -ang);
	cam->uz = quaternion_rot(cam->uz, cam->ux, -ang);
}

void	cam_turn_up(t_cam *cam, double ang)
{
	cam->ux = quaternion_rot(cam->ux, cam->ux, ang);
	cam->uy = quaternion_rot(cam->uy, cam->ux, ang);
	cam->uz = quaternion_rot(cam->uz, cam->ux, ang);
}
