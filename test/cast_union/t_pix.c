/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 12:39:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/01 13:02:26 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef	union	u_pix
{
	int					nb;
	unsigned	char	comp[4];
}				t_pix;

void	test_overflow()
{
	t_pix	g, h;

	int	tmp;
	g.comp[0] = 255;
	h.comp[0] = 100;
	g.comp[2] = ((tmp = g.comp[0] + h.comp[0]) > 255) ? 255 : tmp;
	g.comp[1] = g.comp[0] + h.comp[0];
	printf("tmp:%d	protected:%d	not_protected:%d\n", tmp, g.comp[2], g.comp[1]);
}

void	test_simple_addr_cast()
{
	int		a, b, c, i;
	t_pix	d, e, f, g, h;

	c = 255 << 16 | 2 << 8 | 3;

	d.comp[0] = 1;
	d.comp[1] = 3;
	d.comp[2] = 7;
	d.comp[3] = 15;

	b = *(int*)&d;
	e = *(t_pix*)&c;

	for (i = 0; i < 4; i++)
		printf("comp[%d]:%d\n", i, e.comp[i]);
	
	printf("e.nb:%d	c:%d\n", e.nb, c);
}

int	main()
{
	test_overflow();
	return (0);
}
