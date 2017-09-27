/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:21:49 by fjanoty           #+#    #+#             */
/*   Updated: 2017/09/28 00:28:40 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void	set_plan_test(t_obj *obj)
{
	obj->type = 0;
	vec_set(obj->col, 0, 206, 209); // bleu cian
	vec_set(obj->ang, 0, 0, 0);		
	vec_set(obj->pos, 0, -2, 0);		
	vec_set(obj->dir, 0, -1, 0.1);	// may be obj_set_invrot_dir to adapt obj->dir
	vec_normalise(obj->dir, obj->dir);
	plan_init(obj); 					// dans value on met le coef 'd' de l'eq du plan
}

void	set_sphere_test(t_obj *obj)
{
	obj->type = 1;
	obj->value = 3;
	vec_set(obj->col, 238, 44, 44); // rouge lillte darck
	vec_set(obj->ang, 0, 0, 0);
	vec_set(obj->pos, 2, 3, -5);
	vec_set(obj->dir, 0, 0, 0);
}

void	set_cylindre_test(t_obj *obj)
{
	obj->type = 2;
	obj->value = 1;
	vec_set(obj->col, 239, 28, 98); // move
	vec_set(obj->pos, -5, 2, 0);
	obj_set_invrot(obj, 0,  10 * M_PI / 180, 0);
}

void	set_cone_test(t_obj *obj)
{
	obj->type = 3;
	obj->value = 4;
	vec_set(obj->col, 108, 139, 61); // vert dark olive
	vec_set(obj->ang, 0, 0, 0);
	vec_set(obj->pos, 0, 0, -4);
	obj_set_invrot(obj, 0.1, 0, 0);
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

void	test_init_light(t_light *light, int nb_light)
{
	int	i;

	memset(light, 0, sizeof(t_light) * nb_light);
	i = 0;
	while (i < nb_light)
		light[i++].power = -1; // condition d'arret de la boucle

	// light 0
	vec_set(light[0].pos, 0, 0, -10);
	vec_set(light[0].col, 1, 1, 1); // hume
	light[0].power = 1;
}

void	test_basique(t_env *e)
{
	t_obj	obj[5];
	t_light	light[5];
	(void)e;
	(void)obj;
	(void)light;

//	test_init_obj(obj);
//	test_init_light(light, sizeof(light) / sizeof(t_light));

//	fill_zbuff(&e->scene, &e->item);
//	color_scene(&e->scene, e->item.light, e->item.obj); 
//	mlx_put_image_to_window(e->mlx, e->scene.win, e->scene.img, 0, 0);
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
