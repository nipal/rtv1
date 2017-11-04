/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 11:00:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 11:21:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_DEFINE_H
# define RTV1_DEFINE_H

# define SCENE_X        400
# define SCENE_Y        200

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

# define KEY_WORD_SIZE 16

# define OBJ_TYPE       0
# define ASSETS_COMP    1
# define CAM_COMP       2
# define LIGHT_COMP     3

# define TYPE_ASSET 0
# define TYPE_LIGHT 1
# define TYPE_CAM   2

# define PLAN       0
# define SPHERE     1
# define CYLINDER   2
# define CONE       3

# define RD0 ray_dir.x
# define RD1 ray_dir.y
# define RD2 ray_dir.z
# define RP0 ray_pos.x
# define RP1 ray_pos.y
# define RP2 ray_pos.z

# define DEG  (M_PI / 180)

# define ZERO_P 0.0000001
# define ZERO_N -0.0000001

#endif
