/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rtv1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 18:28:09 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/07 20:42:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/////////////////////////////
#include "file_str.c"
/////////////////////////////

# define VDIM 3

typedef	struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef	struct	s_cam
{
	t_vec3		pos;
	t_vec3		ux;
	t_vec3		uy;
	t_vec3		uz;
}				t_cam;

typedef	struct	s_light
{
	t_vec3		pos;
	t_vec3		col;					// pour l'instant osef
	double		power;					// poura etre une condition d'arret si negatif
}				t_light;

typedef	struct	s_mat3
{
	t_vec3		ux;
	t_vec3		uy;
	t_vec3		uz;
}				t_mat3;

typedef	struct	s_obj
{
	int			type;
	t_vec3		col;					// pour l'instant comme on connais [0, 255] juste ca changera plus tard
	t_mat3		rot_inv;
	t_vec3		ang;	// on peut reconstruire ses transformation
	t_vec3		pos;
	t_vec3		dir;
	double		value;
}				t_obj;


typedef	struct	s_item
{
	double		size_x;
	double		size_y;
	t_cam		*cam;					//		#CAM# on a une copie du pointeur ici qui est declarer dans t_mlx_win
	t_light		*light;
	t_obj		*obj;
	int			nb_light;
	int			nb_obj;
	int			nb_cam;
	double		(*obj_dist[4])(t_obj *obj, t_vec3 ray_pos, t_vec3 ray_dir);
	t_vec3		(*obj_nrm[4])(t_obj *obj, t_vec3 pos_impact);
}				t_item;


int		is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

/*
char	*skip_withe_space(char *str)
{
	while (is_space(*str++))
		;
	return (str);
}
*/

int		skip_withe_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	return (i);
}

int		skip_non_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_space(str[i]))
		i++;
	return (i);
}

double	atol_size(const char *str, int *id)
{
	int		i;
	int		j;
	double		nb;
	double		factor;

	if (id)
		*id = 0;
	if (str)
	{
		i = 0;
		factor = 1;
		nb = 0;
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		if (str[i] == 45 || str[i] == 43)
			factor = 44 - str[i++];
		j = 0;
		while (str[i] >= 48 && str[i] <= 57 && ++j < 15)
			nb = nb * 10 + str[i++] - 48;
		if (id)
			*id = i;
		return (nb * factor);
	}
	return (0);
}

//	int	double_is_neg(double nb)
//	{
//		if (*(unsigned int*)(&nb) & 1 << 31)
//			return (1);
//		return (0);
//	}

int	double_is_neg(double nb)
{
	if (*(unsigned long*)(&nb) & (unsigned long)1 << 63)
		return (1);
	return (0);
}

double	str_get_double(const char *str, int *curs)
{
	double 	nb;
	double	coef;
	long	tmp;
	int		i;
	double	sign;

	nb = (double)atol_size(str, &i);
	sign = (double_is_neg(nb)) ? -1.0 : 1.0;
	nb = (double_is_neg(nb)) ? nb * -1 : nb;
	*curs = i;
	if (str[i] && str[i] == '.'  && str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		tmp = atol_size(str + i + 1, &i);
		coef = 1.0 / pow(10, i);
		nb += tmp * coef;
		*curs += i + 1;
	}
	nb *= sign;
	return (nb);
}

t_vec3	str_get_vec(char *str)
{
	(void)str;
	t_vec3	v;

	v.x = 0;
	return (v);
}

void	test_get_double(const char *str)
{
	int	i;

	printf("%s -> %.20f\n", str, str_get_double(str, &i));
	printf("%s -> %.20f\n", str, atof(str));
}



typedef	unsigned long ul;

void	print_bit(ul toto, int val)
{
	int	i;
	char c;

	c = (toto & 1) ? '1': '0';
	if (++val < 64)
		print_bit(toto >> 1, val);
	printf("%c", c);
}


void	test_double()
{
//	double	toto = -0.0;
//
//	if (double_is_neg(toto))
//		printf("Negative\n");
//	else
//		printf("positive\n");


//	printf("toto:%f\n", toto);
//
//	if (toto == -0.0)
//		printf("===>OUI\n");
//	if (toto == +0.0)
//		printf("----NON\n");
//	printf("-0.0 => %ld\n", *((long*)(&toto)));
//	printf("0.0  => %ld\n", *((long*)(&toto)));

	test_get_double("-0.01234567890123456789 ");
//	test_get_double("-0.09868798798798 ");
//	test_get_double(" -0978  ");
//	test_get_double("0.0");
//	test_get_double("-1.0     ");
//	test_get_double(".0");
//	test_get_double("		.0898");
//	test_get_double("		.0898  lk lk");
//	test_get_double("243");

}

int 	find_char(const char *str, char target)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != target && is_space(str[i]))
		i++;
	return (((str[i] == target) ? i + 1: -1));
}

t_vec3	vec3_null(int i)
{
	static	t_vec3	vec = {0 , 0, 0};

	(void)i;
	return (vec);
}

t_vec3	str_get_vec3(const char *str, int *curs, int *err)
{
	int		add;
	int		i;
	int		coma;
	t_vec3	vec;

	vec.x = str_get_double(str, &i);
	if ((coma = find_char(str + i, ',')) < 0)
		return (vec3_null(*err = -1));
	add = i + coma;
	vec.y = str_get_double(str + add, &i);
	if ((coma = find_char(str + add + i, ',')) < 0)
		return (vec3_null(*err = -1));
	add += i + coma;
	vec.z = str_get_double(str + add, &i);
	*curs = add + i;
	return (vec);
}

void	print_vec3(t_vec3 vec)
{
	printf("x:%f	y:%f	z:%f\n", vec.x, vec.y, vec.z);
}

void	vec3_diff(char *str)
{
	int		i;
	int		err;
	t_vec3	vec;

	err= 0;
	vec = str_get_vec3(str, &i, &err);
	if (err == 0)
		printf("{%s}	==>", str), print_vec3(vec);
	else
		printf("ERROR vec3 not recogonize\n");
}

void	test_vec3()
{
//	vec3_diff(" 0.213, 98, -0.89 ");
	vec3_diff(" ");
//	vec3_diff("0.213,98,-0.89");
}

// on va comencer par les obj simple


void	remove_coment(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
		{
			j = 0;
			while (str[i + j] && str[i + j] != '\n')
				j++;
			memmove(str + i, str + i + j, strlen(str + i + j) + 1);
		}
		i++;
	}
}

/*
**	Il sagit de prendre un mot et dire si quel valeur on incremente
*/


//	obj: 	plan, sphere, cylindre, cone
//	light
//	camera

void	obj_add_value(t_obj *obj, char *str, int *curs)
{

}

# define OBJ_TYPE 		0
# define ASSETS_COMP	1
# define CAM_COMP		2
# define LIGHT_COMP		3


char	*get_tab(int tab_nb, int *size)
{
	static	char	object_type[6][16] = {"light", "camera", "plan", "sphere", "cylinder", "cone"};
	static	char	assets_comp[][16] = {"pos", "dir", "col", "ang"};
	static	char	cam_comp[][16] = {"pos", "dir", "up" };
	static	char	light_comp[][16] = {"pos", "col"};

	if (!size)
		return (NULL);
	if (tab_nb == OBJ_TYPE && (*size = 6))
		return ((char*) object_type);
	if (tab_nb == ASSETS_COMP && (*size = 4))
		return ((char*) assets_comp);
	if (tab_nb == CAM_COMP && (*size = 3))
		return ((char*) cam_comp);
	if (tab_nb == LIGHT_COMP && (*size = 3))
		return ((char*) light_comp);
	return (NULL);
}

int		find_id_from_name(char *str, int tab_nb)
{
	int		i;
	char	*toto;
	int		size;

	toto = get_tab(tab_nb, &size);
	i = 0;
	while (i < size)
	{
		if (!strcmp(toto + 16 * i, str))
			return (i);
		i++;
	}
	return (-1);
}
/*
 

# define OBJ_TYPE 		0
# define ASSETS_COMP	1
# define CAM_COMP		2
# define LIGHT_COMP		3

 * */

int	main()
{
//	test_double();
//	test_vec3();


	char	*file_str = get_file_str();

	remove_coment(file_str);
//	printf("%s\n", file_str);

	int	i;
	int	j;
	int	id_;

	char truc[] = "plan";
	printf("%s: %d\n", truc, find_id_from_name(truc, 0));
	return (0);
	i = 0;
	while (file_str[i])
	{
		i += skip_withe_space(file_str + i);
		j = skip_non_space(file_str + i);
		i += j;
	}
	free (file_str);
	return (0);
}

/*
**	Tan qu'on est pas a la fin du fichier
**		[ skip with space ]
**		[ get obj_name ]
**			[ skip with space ]
**			[ get_param_name ]
**				[get_param_value]
**
**				
*/

/*
**
**	On pourrait faire pour une structure un peu comme les base de donner:
**		en gros des structure qui lie : mot_clef, fonction/indice de traitement, 
*/


// On pourais aussi faire pouvoir editer des parametre comme:
// 		- taille de la fenetre
// 		- vitesse: (translation, rotation)
