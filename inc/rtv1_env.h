/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_env.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 11:11:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 11:28:10 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_ENV_H
# define RTV1_ENV_H

# include "rtv1.h"
# include "quaternion.h"
# include "mlx_key.h"
# include "libft.h"
# include "rtv1_define.h"
# include "rtv1_typedef.h"
# include "rtv1_prototype.h"
# include "rtv1_env.h"

typedef	struct			s_env
{
	void			*mlx;
	t_mlx_win		scene;
	double			(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3			(*obj_nrm[4])(t_obj *obj, t_vec3 pos_impact);
	t_item			item;
	long			frame;
	long			last_frame;
	int				visual_debug;
}						t_env;

#endif
