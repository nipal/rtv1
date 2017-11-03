/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 19:46:06 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 00:04:58 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_putstr(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return ((int)i);
}


char	*reverse(char *s)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = strlen(s) - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
	return (s);
}

char	*ft_ltoa(long n)
{
	int		i;
	long	sign;
	char	*s;

	s = (char*)malloc(30);
	bzero(s, 30);
	if (n == 0)
		return (strcpy(s, "0"));
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		s[i++] = n % 10 + '0';
		n /= 10;
	}
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	return (reverse(s));
}

void	print_double(double val, int precision)
{
	double	pow;
	long	nb;
	char	*str;

	if (precision < 0)
		precision = 0;
	if (precision >= 30)
		precision = 30;
	if (val < 0.0)
		ft_putstr("-");
	val = fabs(val);
	pow = powf(10, precision);
	nb = (long)val;
	str = ft_ltoa(nb);
	ft_putstr(str);
	free(str);
	ft_putstr(".");
	nb = fmod(fabs(val * pow), pow);
	str = ft_ltoa(nb);
	ft_putstr(str);
	free(str);
}

void	test_print_double_endl(double nb)
{
	ft_putstr("-->");
	print_double(nb, 10);
	ft_putstr("\n");
	printf("==>%.10f\n", nb);
}

void	test_print_double()
{
	double	yolo;
	test_print_double_endl(1);
	test_print_double_endl(0);
	test_print_double_endl(0.1);
	test_print_double_endl(0.235);
	test_print_double_endl(0.543634);
	test_print_double_endl(0.452234);
	test_print_double_endl(0.1337);
	test_print_double_endl(M_PI);
	test_print_double_endl(123456789.987654321);
	printf("\n\n	neg_part\n\n\n");
	test_print_double_endl(-1);
	test_print_double_endl((yolo = -0.0));
	test_print_double_endl(-0.1);
	test_print_double_endl(-0.1337);
	test_print_double_endl(-0.235);
	test_print_double_endl(-0.543634);
	test_print_double_endl(-0.452234);
	test_print_double_endl(-0.1337);
	test_print_double_endl(-M_PI);
	test_print_double_endl(-123456789.987654321);

}

void	test_simple_double_convert()
{
	double	d;
	double	pow;
	long	l1, l2;

	d = 42.1337;
	pow = powf(10, 4);
	l1 = (long)d;
	l2 = fmod(d * pow, pow);
	printf("l1:%ld	l2:%ld\n", l1, l2);
}

void	test_zero_neg()
{
	if ((-0.0) < 0)
		printf("yes it is\n");
	else
		printf("sory but not sory\n");
}

int	main()
{
	test_print_double();
//	test_print_double_endl(-0.235);
//	test_zero_neg();
	return (0);
}
