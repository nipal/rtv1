/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_long_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 20:14:58 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/03 20:18:07 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main()
{
//	long	l = -9223372036854775808;	

	long l;
	unsigned	long ul;

	ul = -1;
//	l = ul;
	printf("%lu\n", ul);
	return (0);
}
