/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:11:39 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/03 18:25:37 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned	char	*src_u;
	unsigned	char	*dst_u;
	size_t				i;

	src_u = (unsigned char *)src;
	dst_u = (unsigned char *)dst;
	if (src_u <= dst_u)
		while (len--)
		{
			dst_u[len] = src_u[len];
		}
	else
	{
		i = 0;
		while (i < len)
		{
			dst_u[i] = src_u[i];
			i++;
		}
	}
	return (dst);
}
