/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:24:36 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 05:26:43 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			skip_withe_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	return (i);
}

int			skip_non_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_space(str[i]))
		i++;
	return (i);
}

int			find_char(const char *str, char target)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != target && is_space(str[i]))
		i++;
	return (((str[i] == target) ? i + 1 : -1));
}

int			find_char_force(const char *str, char target)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != target)
		i++;
	return (((str[i] == target) ? i + 1 : -1));
}

int			get_word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_alphanum(str[i]))
		i++;
	return (i);
}
