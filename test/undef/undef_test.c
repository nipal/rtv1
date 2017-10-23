/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undef_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 23:57:56 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/18 10:59:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

typedef unsigned long ul;
void	print_bit(unsigned long toto, int val)
{
	char c;

	c = (toto & 1) ? '1': '0';
	if (++val < 64)
		print_bit(toto >> 1, val);
	if (val % 4 == 0)
		printf(" ");
	printf("%c", c);
}

int	main()
{
	double a = 1;
	double b = 0;
	double	toto = b / b;
	double	tata = asin(987);
	double  titi, tutu, wesh;
	ul yolo;

	titi = -tata;//*(double*)((ul*)&(tata)); 
	tutu = -a / b;

	yolo = *(ul*)&(toto);
	yolo ^= (ul)1 << 51;

//	yolo = (ul)1 << 51 | (ul)1 << 52 ;
	wesh = *(double*)&yolo;
	printf("\n");
	printf("wesh:%f\n", wesh);
	print_bit(yolo, 0);
	printf("\n");

	printf("%f\n", toto);
	printf("%f\n", tata);
	printf("%f\n", titi);
	printf("%f\n", tutu);




	print_bit(*(ul*)&toto, 0);
	printf("\n");
	print_bit(*(ul*)&tata, 0);

	printf("\n");
	print_bit(*(ul*)&titi, 0);

	printf("\n");
	print_bit(*(ul*)&tutu, 0);
	return (0);
}
