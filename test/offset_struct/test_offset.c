/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_offset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 11:45:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/11 12:20:52 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef	struct	s_tata
{
	double	a;
	double	b;
	double	c;
}				t_tata;

typedef	struct	s_test
{
	double	v1;
	double	v2;
	t_tata	t1;
	t_tata	t2;
}				t_test;

size_t	get_offset_test(int comp)
{
	t_test	tt;

	switch (comp)
	{
		case 0:
			return ((size_t)&tt.v1 - (size_t)&tt);
		case 1:
			return ((size_t)&tt.v2 - (size_t)&tt);
		case 2:
			return ((size_t)&tt.t1 - (size_t)&tt);
		case 3:
			return ((size_t)&tt.t2 - (size_t)&tt);
	}
	return (0);
}

t_tata	get_tata(double k)
{
	t_tata	t;

	t.a = 0 * k;
	t.b = 1 * k;
	t.c = 2 * k;
	return (t);
}

void	print_test(t_test tt)
{
	printf("v1:%f	v2:%f\nt1[a:%f, b:%f, c:%f]\nt2[a:%f, b:%f, c:%f]\n", tt.v1, tt.v2, tt.t1.a, tt.t1.b, tt.t1.c, tt.t2.a, tt.t2.b, tt.t2.c);
}

int	main()
{
	t_test	te;
	t_tata	*pt_struct, *t1, *t2;
	double	*pt_double, *a, *b, *c, *d;



	//tmp1 = (t_tata*);

	int	i;
	for (i = 0; i < 4; i++)
	{
		printf("[%d]->%zu\n", i, get_offset_test(i));
	}
 
	a  = (double*)((long)&te + (long)get_offset_test(0));
	b  = (double*)((long)&te + (long)get_offset_test(1));
	t1 = (t_tata*)((long)&te + (long)get_offset_test(2));
	t2 = (t_tata*)((long)&te + (long)get_offset_test(3));

	printf("%ld\n", (long)((long)b - (long)a));

	
//	pt_double = (double*)(&te + get_offset_test(1));
//	*pt_double = 666;

	*a = 666;
	*b = 27.08;
	*t1 = get_tata(1);
	*t2 = get_tata(2);
	print_test(te);

//	*((double*)(&te + get_offset_test(0))) = 3.14159;
//	*((double*)(&te + get_offset_test(1))) = 8.27;
//	*((t_tata*)(&te + get_offset_test(2))) = get_tata();
//	*((t_tata*)(&te + get_offset_test(3))) = get_tata();
//	print_test(te);
	return (0);
}
