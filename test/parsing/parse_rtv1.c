/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rtv1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 11:10:49 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/06 15:31:02 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

# define VDIM 3


typedef	struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef	union	u_axes
{
	float		comp[VDIM][VDIM];
	float		all[VDIM * VDIM];
}				t_axes;

typedef	struct	s_basis
{
	float		pos[3];
	float		*axes[VDIM];
	float		ux[VDIM];
	float		uy[VDIM];
	float		uz[VDIM];
}				t_basis;

int		is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (1);
}

float	atol_size(const char *str, int *id)
{
	int		i;
	int		j;
	float		nb;
	float		factor;

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

int	float_is_neg(float nb)
{
	if (*(unsigned int*)(&nb) & 1 << 31)
		return (1);
	return (0);
}

int	double_is_neg(double nb)
{
	if (*(unsigned long*)(&nb) & (unsigned long)1 << 63)
		return (1);
	return (0);
}

float	str_get_float(const char *str, int *curs)
{
	float 	nb;
	float	coef;
	long	tmp;
	int		i;
	float	sign;

	nb = (float)atol_size(str, &i);
	sign = (float_is_neg(nb)) ? -1.0 : 1.0;
	nb = (float_is_neg(nb)) ? nb * -1 : nb;	
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

void	test_get_float(const char *str)
{
	int	i;

	printf("%s -> %.20f\n", str, str_get_float(str, &i));
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


void	test_float()
{
//	double	toto = -0.0;
//	
//	if (float_is_neg(toto))
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

	test_get_float("-0.01234567890123456789 ");
//	test_get_float("-0.09868798798798 ");
//	test_get_float(" -0978  ");
//	test_get_float("0.0");
//	test_get_float("-1.0     ");
//	test_get_float(".0");
//	test_get_float("		.0898");
//	test_get_float("		.0898  lk lk");
//	test_get_float("243");

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

	vec.x = str_get_float(str, &i);
	if ((coma = find_char(str + i, ',')) < 0)
		return (vec3_null(*err = -1));
	add = i + coma;
	vec.y = str_get_float(str + add, &i);
	if ((coma = find_char(str + add + i, ',')) < 0)
		return (vec3_null(*err = -1));
	add += i + coma;
	vec.z = str_get_float(str + add, &i);
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

int	main()
{
//	test_float();
//	test_vec3();
	char *str = strdup("oui ----> #ceci est un comentaire\nEt la c'est normale ######\nYoupi\n#123456789\n");

	str = strdup(
"cone\n\
{\n\
	pos:	0, -3, 5\n\
	col:	108, 139, 61\n\
	dir:	0, 1, 0\n\
	coef:	1\n\
}"
);

	printf("%s\n", str);	
//	printf("============ before =========:\n%s\n", str);
//	remove_coment(str);
//	printf("============ after  =========:\n%s\n", str);
//	free (str);
	return (0);
}
