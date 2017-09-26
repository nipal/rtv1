/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:21:49 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/26 20:47:20 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void	set_plan_test(t_obj *obj)
{
	obj->type = 0;
	vec_set(obj->ang, 0, 0, 0);		
	vec_set(obj->pos, 0, -2, 0);		
	vec_set(obj->dir, 0, -1, 0.1);
	vec_normalise(obj->dir, obj->dir);
	plan_init(obj); 					// dans radius on met le coef 'd' de l'eq du plan
}

void	set_sphere_test(t_obj *obj)
{
	obj->type = 1;
	obj->radius = 1;
	vec_set(obj->ang, 0, 0, 0);
	vec_set(obj->pos, -2, 3, -5);
	vec_set(obj->dir, 0, 0, 0);
}

void	set_cylindre_test(t_obj *obj)
{
	obj->type = 2;
	obj->radius = 4;
	vec_set(obj->ang, 0, 0, 0);
	vec_set(obj->pos, 0.1, 0.1, 4);
	vec_set(obj->dir, 1, 1, 1);
}

void	set_cone_test(t_obj *obj)
{
	obj->type = 3;
	obj->radius = 4;
	vec_set(obj->ang, 0, 0, 0);
	vec_set(obj->pos, 0, 0, -4);
	vec_set(obj->dir, 1, 1, 1);
}

void	test_init_obj(t_obj *obj)
{
	int	i = 0;
	
	memset(obj, 0, sizeof(obj) * 5);
	for (i = 0; i < 5; i++)
		obj[i].type = -1;
	i = 0;
	set_plan_test(obj + i++);
	set_sphere_test(obj + i++);
	set_cylindre_test(obj + i++);
	set_cone_test(obj + i++);

//	obj[4].type = -1;		// la fin de la serie d'objet
}


void	test_basique(t_env *e)
{
	t_obj	obj[5];
	(void)e;
	(void)obj;

	test_init_obj(obj);

	fill_zbuff(&e->scene, &e->scene.cam, obj);
	color_scene(&e->scene, obj); 
	mlx_put_image_to_window(e->mlx, e->scene.win, e->scene.img, 0, 0);
//	basis_describe(&e->cam);
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
