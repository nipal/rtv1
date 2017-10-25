/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undef_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 23:57:56 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/24 21:50:19 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

void	print_bit_str(ul toto, int val, char *str)
{
	char c;
	int	bit_size;

	bit_size = sizeof(toto) * 8;

	str[bit_size - val - 1] = (toto & 1) ? '1': '0';
	if (++val < bit_size)
		print_bit_str(toto >> 1, val, str);
	else
		str[bit_size] = '\0';
}

void	test_undef_inf_val()
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

}


void	test_comparaison(double a, double b)
{
	printf("===============\n");
	printf("a:%f	b:%f\n\n", a, b);
	printf("a < b : %s\n", (a < b) ? "yes" : "no");
	printf("a > b : %s\n", (a > b) ? "yes" : "no");
	printf("a <= b : %s\n", (a <= b) ? "yes" : "no");
	printf("a >= b : %s\n", (a >= b) ? "yes" : "no");
	printf("a == b : %s\n", (a == b) ? "yes" : "no");
	printf("a != b : %s\n", (a != b) ? "yes" : "no");
	printf("\n");
}

int	main()
{
	double	inf_p, inf_p2, inf_n, undef, a, b, c, d;
	char	nb1[65], nb2[65], nb3[65], nb4[65];

	a = 1;
	b = -1;
	c = 0;

	inf_p = a / c;
	inf_p2 = a / c;
	inf_n = b / c;
	undef = 0.0 / 0.0;

	d = 1.0 / 0.0;

//	*(ul*)&undef ^= (ul)1 << 63; // avec le petit truc qui va bien pour manipuler un double avec des operatuer binaire
//	*(ul*)&inf_p2 ^= (ul)1 << 4; // avec le petit truc qui va bien pour manipuler un double avec des operatuer binaire

	print_bit_str(*(ul*)&inf_p, 0, nb1);
	print_bit_str(*(ul*)&inf_p2, 0, nb4);
	print_bit_str(*(ul*)&inf_n, 0, nb2);
	print_bit_str(*(ul*)&undef, 0, nb3);
	printf("\n\ninf_P:%f||	%s\ninf_p2:%f||	%s\ninf_n:%f||	%s\nundef:%f||	%s\n", inf_p, nb1, inf_p2, nb4, inf_n, nb2, undef, nb3);


//	*(ul*)&inf_p2 ^= (ul)1 << 0; // avec le petit truc qui va bien pour manipuler un double avec des operatuer binaire
//	print_bit_str(*(ul*)&inf_p2, 0, nb4);
//	printf("inf_p2:%f||	%s\n", inf_p2, nb4);

	printf("\n\n%f is %s than %f\n", inf_p, (inf_p > a) ? ">" : "<", a);
	printf("%f is %s than %f\n", inf_p, (inf_p > inf_p) ? ">" : "<", inf_p);
	printf("%f is %s than %f\n", inf_p, (inf_p < inf_p) ? "<" : ">", inf_p);
	printf("%f is %s to %f\n", inf_p, (inf_p == inf_p) ? "==" : "!=", inf_p);

	printf("\n\n%f is %s than %f\n", inf_p, (inf_p < a) ? "<" : ">", a);
	printf("%f is %s than %f\n", inf_p, (inf_p > inf_p2) ? ">" : "<", inf_p2);
	printf("%f is %s than %f\n", inf_p, (inf_p < inf_p2) ? "<" : ">", inf_p2);
	printf("%f is %s to %f\n", inf_p, (inf_p == inf_p2) ? "==" : "!=", inf_p2);

//	test_comparaison(inf_p, inf_p);
//	test_comparaison(inf_p, 1);
//	test_comparaison(inf_p, inf_n);
//	test_comparaison(inf_p, undef);
//
//	printf("\n********\n");
//	test_comparaison(inf_n, inf_p);
//	test_comparaison(inf_n, 1);
//	test_comparaison(inf_n, inf_n);
//	test_comparaison(inf_n, undef);
//	printf("\n********\n");
//	test_comparaison(undef, inf_p);
//	test_comparaison(undef, 1);
//	test_comparaison(undef, inf_n);
//	test_comparaison(undef, undef);

	return (0);
}

/*
**	
**		pour +-inf et nan : l'exposant est remplis, 
**			pour +- inf,	le signe determine le singe
**			pour nana, 		peu importe le signe
**
**			inf et nan se differencie pck pour nan la mantisse est != de 0 pour inf la mentisse == 0
**
**	inf et -inf:	valeur 		=>  on une valeur precise: le bit de signe, l'exposant full de 1, et la mentisse a 0
**					comparaison	=> inf se comprare normalement a tout les nombre, c'est comme si c'etait le plus grand des nombre donc +inf == +inf et +inf <= +inf
**									et donc la logique se poursuit avec -inf
**	nan				valeur		=> signe: peut importe | exposant: tout remplis de 1 | mentisse: peut importe, souvent 0 
**					comparaison	=> il reponp non a tout donc nan < 0 => FALSE ET nan >= 0 ==> FALSE, sauf pour != ou il repond vrai a tout, meme a lui meme alors qu'on compare la meme variable 
*/
