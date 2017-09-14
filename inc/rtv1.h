/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 00:49:15 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/15 01:25:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV!_H
# define RTV1_H

typedef	union	u_pix
{
	int			nb;
	char		comp[4];
}				t_pix;

typedef	struct	s_win_mlx
{
	void		*img;
	void		*win;
	int			depth;
	int			endian;
	t_pix		*data;
	char		*name;
	int			size_x;
	int			size_y;
	float		*mouse[3];				//	position
	float		*prev_mouse[3];			// prev pposition
}				t_win_mlx;

#endif
