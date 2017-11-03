/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ok.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 08:38:44 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 08:44:35 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main()
{
	double	a, b;

	a = 1.0 / 0.0;
	b = 1.0 / 0.0;
	printf("a:%f\n", a);
	printf("b:%f\n", b);
	printf("a + b : %f\n", (a + b));
	printf("a - b : %f\n", (a - b));
	printf("-a - b : %f\n", (-a - b));
	printf("!a:%f\n", !a);
	printf("(int)a:%d\n", (int)a);
	printf("(long)a:%ld\n", (long)a);
	printf("(long_int)a:%ld\n", (int)a);
	printf("(int)(long)al:%ld\n", (int)(long)a);
	printf("(int)(long)a:%d\n", (int)(long)a);
	return (0);
}
