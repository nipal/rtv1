/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:38:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 00:07:00 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include "../inc/libft.h"

//void	vec3_print(t_vec3 vec)
//{
//	ft_putstr("x:");
//	print_double(vec.x, 10);
//	ft_putstr("y:");
//	print_double(vec.y, 10);
//	ft_putstr("z:");
//	print_double(vec.z, 10);
//}

void	vec3_print_str(t_vec3 vec, char *str)
{
	ft_putstr(str);
	ft_putstr("\t");
	print_double(vec.x, 10);
	ft_putstr(", ");
	print_double(vec.y, 10);
	ft_putstr(", ");
	print_double(vec.z, 10);
	ft_putstr("\n");
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
