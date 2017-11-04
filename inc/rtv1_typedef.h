/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_typedef.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 11:01:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 11:28:11 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_TYPEDEF_H
# define RTV1_TYPEDEF_H

# include "rtv1.h"
# include "quaternion.h"
# include "mlx_key.h"
# include "libft.h"
# include "rtv1_define.h"
# include "rtv1_typedef.h"
# include "rtv1_prototype.h"
# include "rtv1_env.h"

typedef	struct			s_lst
{
	char				cpy;
	void				*ptr;
	struct s_lst		*next;
}						t_lst;

typedef	struct			s_seg
{
	t_vec3	from;
	t_vec3	to;
	t_vec3	c1;
	t_vec3	c2;
}						t_seg;

typedef	struct			s_index
{
	int			i;
	int			j;
}						t_index;

typedef	struct			s_val
{
	double	v1;
	double	v2;
}						t_val;

typedef	union			u_pix
{
	int					nb;
	unsigned	char	comp[4];
}						t_pix;

typedef	struct			s_zbuff
{
	int					id;
	double				dist;
	t_vec3				nrm;
	t_vec3				pos;
}						t_zbuff;

typedef	struct			s_light
{
	t_vec3				pos;
	t_vec3				col;
	double				power;
}						t_light;

typedef	struct			s_cam
{
	t_vec3				pos;
	t_vec3				ux;
	t_vec3				uy;
	t_vec3				uz;
}						t_cam;

typedef	struct			s_mlx_win
{
	t_env				*env;
	void				*img;
	void				*win;
	t_cam				*cam;
	int					depth;
	int					endian;
	t_pix				*data;
	t_zbuff				*zbuff;
	char				*name;
	int					size_x;
	int					size_y;
	t_vec3				mouse;
	t_vec3				prev_mouse;
	int					refresh;
}						t_mlx_win;

typedef	struct			s_obj
{
	int					type;
	t_vec3				col;
	t_mat3				rot_inv;
	t_vec3				pos;
	t_vec3				dir;
	double				value;
	double				pow_spec;
}						t_obj;

typedef	struct			s_item
{
	double		size_x;
	double		size_y;
	t_light		*light;
	t_obj		*obj;
	t_cam		*cam;
	t_cam		*all_cam;
	int			id_cam;
	int			nb_cam;
	int			nb_light;
	int			nb_obj;
	double		(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_dist_all[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_nrm[4])(t_obj *obj, t_vec3 pos_impact);
	t_lst		*all_segment;
}						t_item;

typedef	struct			s_entities
{
	int					type;
	int					sub_type;
	void				*entities;
	struct s_entities	*next;
}						t_entities;

#endif
