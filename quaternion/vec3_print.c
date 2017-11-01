/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:38:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 17:33:11 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "../inc/libft.h"

void	print_double(double val)
{
	printf("%f", val);
}

void	vec3_print(t_vec3 vec)
{
	ft_putstr("x:");
	print_double(vec.x);
	ft_putstr("y:");
	print_double(vec.y);
	ft_putstr("z:");
	print_double(vec.z);
}

void	vec3_print_str(t_vec3 vec, char *str)
{
	ft_putstr(str);
	ft_putstr("x:");
	print_double(vec.x);
	ft_putstr("y:");
	print_double(vec.y);
	ft_putstr("z:");
	print_double(vec.z);
}

void	mat3_print_str(t_mat3 m, char *str)
{
	ft_putstr(str);
	ft_putstr("\n{");
	vec3_print_str(m.ux, "	ux:");
	vec3_print_str(m.uy, "	uy:");
	vec3_print_str(m.uz, "	uz:");
	ft_putstr("}\n");
}
