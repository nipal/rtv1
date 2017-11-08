/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:25:52 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 05:26:37 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		atol_size(const char *str, int *curs)
{
	int			i;
	int			j;
	double		nb;
	double		factor;

	if (curs)
		*curs = 0;
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
		if (curs)
			*curs = i;
		return (nb * factor);
	}
	return (0);
}

double		str_get_double(const char *str, int *curs)
{
	double	nb;
	double	coef;
	long	tmp;
	int		i;
	double	sign;

	nb = (double)atol_size(str, &i);
	sign = (double_is_neg(nb)) ? -1.0 : 1.0;
	nb = (double_is_neg(nb)) ? nb * -1 : nb;
	*curs = i;
	if (str[i] && str[i] == '.' && str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		tmp = atol_size(str + i + 1, &i);
		coef = 1.0 / pow(10, i);
		nb += tmp * coef;
		*curs += i + 1;
	}
	nb *= sign;
	return (nb);
}

t_vec3		vec3_null(int i)
{
	static	t_vec3	vec = {0, 0, 0};

	(void)i;
	return (vec);
}

t_vec3		str_get_vec3(const char *str, int *curs, int *err)
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
