/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:21:49 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/12 17:25:13 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void	set_plan_test(t_obj *obj)
{
	obj->type = 0;
	obj->col = vec3_set(0, 206, 209); // bleu cian
	obj->ang = vec3_set(0, 0, 0);		
	obj->pos = vec3_set(0, -2, 0);		
	obj->dir = vec3_set(0, -1, 0.1);	// may be obj_set_invrot_dir to adapt obj->dir
	obj->dir = vec3_normalise(obj->dir);
	plan_init(obj); 					// dans value on met le coef 'd' de l'eq du plan
}

void	set_sphere_test(t_obj *obj)
{
	obj->type = 1;
	obj->value = 2;
	obj->col = vec3_set(238, 44, 44); // rouge lillte darck
	obj->ang = vec3_set(0, 0, 0);
	obj->pos = vec3_set(2, 3, -3);
	obj->dir = vec3_set(0, 0, 0);
}

void	set_cylindre_test(t_obj *obj)
{
	obj->type = 2;
	obj->value = 1;
	obj->col = vec3_set(239, 28, 98); // move
	obj->pos = vec3_set(-5, 2, 0);
	obj_set_invrot(obj, 0,  10  * DEG, 0);
}

void	set_cone_test(t_obj *obj)
{
	obj->type = 3;
	obj->value = 1;
	obj->col = vec3_set(108, 139, 61); // vert dark olive
	obj->pos = vec3_set(0, -3, -5);
	obj_set_invrot(obj, 80 * DEG, 20 * DEG, 0);
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
	light[0].pos = vec3_set(0, 0, -7);
	light[0].col = vec3_set(1, 1, 1); // hume
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

//void	launch_ray(t_mlx_win *w, t_item *item)
//	launch_ray(&e->scene, &e->item);
//	color_scene(&e->scene, e->item.light, e->item.obj); 
//	mlx_put_image_to_window(e->mlx, e->scene.win, e->scene.img, 0, 0);
//	basis_describe(&e->cam);
//	mlx_do_sync(e->mlx);
}

void	print_vec(double vec[3])
{
	double	norme;

	norme = vec_get_norme(vec);
	printf("vec:|{%f, %f, %f}| = %f\n", vec[0], vec[1], vec[2], norme);
}

void	rotation_test()
{
	int		i;
	double	rot[3][3];
	double	vec[3] = {0, 0, 1};
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

void	test_cam_axes(t_cam *c)
{
	// vecteur unitaire			(norme == 1)
	printf("nrm_ux:%f\n", vec3_norme(c->ux));
	printf("nrm_uy:%f\n", vec3_norme(c->uy));
	printf("nrm_uz:%f\n", vec3_norme(c->uz));
	// vecteur orogonaux		(ux dot uy == 0)
	printf("ux . uy:%f\n", vec3_dot(c->ux, c->uy));
	printf("uy . uz:%f\n", vec3_dot(c->uy, c->uz));
	printf("uz . ux:%f\n", vec3_dot(c->uz, c->ux));
	// vecteur orienter selon 	(ux ^ uy = uz) ==> norme de diff avec e resulta
	printf("||(ux ^ uy) - uz||:%f\n", vec3_norme(vec3_sub(vec3_cross(c->ux, c->uy), c->uz)));
	printf("||(uy ^ uz) - ux||:%f\n", vec3_norme(vec3_sub(vec3_cross(c->uy, c->uz), c->ux)));
	printf("||(uz ^ ux) - uy||:%f\n", vec3_norme(vec3_sub(vec3_cross(c->uz, c->ux), c->uy)));


	printf("==================================\n");
	t_vec3	u1, u2, u3;

	u1 = vec3_set(0, 1, 0);
	u2 = vec3_set(1, 0, 0);
	u3 = vec3_cross(u1, u2);
	vec3_print_str(u1, "u1");
	vec3_print_str(u2, "u2");
	vec3_print_str(u3, "u3");
	printf("==================================\n");
}
