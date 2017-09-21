/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:21:49 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/21 15:58:52 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	test_init_obj(t_obj *obj)
{
	ft_bzero(obj, sizeof(obj) * 5);
	obj[0].type = 1;
	obj[0].radius = 4;
	vec_set(obj->ang, 0, 0, 0);
	vec_set(obj->pos, 0, 0, 10);
	vec_set(obj->dir, 0, 1, 0);

	obj[1].type = -1;
}


void	test_basique(t_env *e)
{
	t_obj	obj[5];
	(void)e;
	(void)obj;

	test_init_obj(obj);

	fill_zbuff(e, &e->scene, &e->cam, obj);
	color_scene(&e->scene, obj); 
	mlx_put_image_to_window(e->mlx, e->scene.win, e->scene.img, 0, 0);
	basis_describe(&e->cam);
//	mlx_do_sync(e->mlx);
}

void	print_vec(float vec[3])
{
	float	norme;

	norme = vec_get_norme(vec);
	printf("vec:|{%f, %f, %f}| = %f\n", vec[0], vec[1], vec[2], norme);
}

void	rotation_test()
{
	int		i;
	float	rot[3][3];
	float	vec[3] = {0, 0, 1};
//	basis	cam;

//	basis_reset(&cam);
	mat_set_one_rot(rot, 1, 2, 1.0 * (2.0 * M_PI / 360.0)); // autoure de X
	i = 0;
	while (i < 360)
	{
		mat_mult_vec(rot, vec, vec);
		print_vec(vec);
		i++;
	}

}
