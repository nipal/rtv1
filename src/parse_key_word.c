/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_key_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:27:36 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 06:12:14 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*get_tab(int tab_nb, int *siz)
{
	static	char	object_type[][KEY_WORD_SIZE] = {"plan", "sphere",
		"cylinder", "cone", "light", "camera"};
	static	char	assets_comp[][KEY_WORD_SIZE] = {"value", "pos", "dir",
		"col", "spec"};
	static	char	cam_comp[][KEY_WORD_SIZE] = {"pos", "dir"};
	static	char	light_comp[][KEY_WORD_SIZE] = {"pos", "col"};

	if (!siz)
		return (NULL);
	if (tab_nb == OBJ_TYPE && (*siz = (sizeof(object_type) / KEY_WORD_SIZE)))
		return ((char*)object_type);
	if (tab_nb == ASSETS_COMP && (*siz = (sizeof(assets_comp) / KEY_WORD_SIZE)))
		return ((char*)assets_comp);
	if (tab_nb == CAM_COMP && (*siz = (sizeof(cam_comp) / KEY_WORD_SIZE)))
		return ((char*)cam_comp);
	if (tab_nb == LIGHT_COMP && (*siz = (sizeof(light_comp) / KEY_WORD_SIZE)))
		return ((char*)light_comp);
	return (NULL);
}

int			find_id_from_name(char *word, int *add_curs, int tab_id)
{
	int		i;
	int		off7;
	char	*tab_key_word;
	int		size_tab;
	int		size_word;

	if (!add_curs)
		return (-1);
	off7 = skip_withe_space(word);
	size_word = get_word_size(word + off7);
	tab_key_word = get_tab(tab_id, &size_tab);
	*add_curs += off7 + size_word;
	if (size_word <= 0)
	{
		(*add_curs)++;
		return (-1);
	}
	i = 0;
	while (i < size_tab)
	{
		if (!strncmp(tab_key_word + KEY_WORD_SIZE * i, word + off7, size_word))
			return (i);
		i++;
	}
	return (-1);
}
