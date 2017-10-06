/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 20:20:28 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/06 14:48:43 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//	compile (adapt name)
// 	open file
//	
char	*get_all_file(const char *file_path);
void	remove_comment();
void	set_obj_cam_light(t_item *item, int *nb_obj, int *nb_cam, int *nb_light);


int		obj_get_type(char *str)
{
	static	char	type_val[][16] = {"light", "camera", "plan", "sphere"
		, "cylindre", "cone"};
	static	char	name_val[][2][16] = {{"pos", "f, f, f"}
		, {}
	};
	int	i;
	int	max;
	(void)name_val;
	(void)type_val;

	i = 0;
	max = sizeof(type_val) / 16;
	while (i < max)
	{
		if (ft_strcmp(str, type_val[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (1);
}

long	atol_size(char *str, int *id)
{
	int		i;
	long	nb;
	int		factor;

	if (id)
		id = 0;
	if (str)
	{
		i = 0;
		factor = 1;
		nb = 0;
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		if (str[i] == 45 || str[i] == 43)
			factor = 44 - str[i++];
		while (str[i] >= 48 && str[i] <= 57)
			nb = nb * 10 + str[i++] - 48;
		if (id)
			*id = i;
		return (nb * factor);
	}
	return (0);
}

float	str_get_float(char *str, int *curs)
{
	double 	nb;
	long	tmp;
	int		i;
	int		sign;

	nb = (double)atol_size(str, &i);
	sign = (nb < 0) ? -1 : 1;
	nb = (nb < 0) ? nb * -1 : nb;	
	*curs = i;
	if (str[i] && str[i] == '.'  && str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		tmp = atol_size(str + i + 1, &i);
		nb += (double)tmp / pow(10, i);
		*curs += i;
	}
	return ((float)(sign * nb));
}

t_vec3	str_get_vec(char *str)
{
	(void)str;
	t_vec3	v;

	v.x = 0;
	return (v);
}

void	rtv1_parse_file(char *file_content, int file_size, t_item *item)
{
	(void)file_content;
	(void)item;
	(void)file_size;
	
}

