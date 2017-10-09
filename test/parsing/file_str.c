/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 17:32:30 by fjanoty           #+#    #+#             */
/*   Updated: 2017/10/09 22:29:29 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*get_file_str()
{
	static	char	*str = NULL;

	if (!str)
	{
		str = strdup(
"\
\n\
\n\
\n\
light\n\
{\n\
	pos		0, 0, 0\n\
	col		255, 255, 255 # couleur + puissance...\n\
}\n\
\n\
camera\n\
{\n\
	pos		0, 0, 0\n\
	up		0, 1, 0\n\
	dir		0, 0, 1\n\
}\n\
\n\
plan\n\
{\n\
	pos		0, -2, 0\n\
	col		0,    206, 209\n\
	dir		0, -1, 0.1\n\
}\n\
\n\
sphere\n\
{\n\
	pos		2, 3, -3\n\
	col		255, 255, 255\n\
	coef	3\n\
}\n\
\n\
cylinder\n\
{\n\
	pos		2, 3, -3\n\
	col		239, 28, 98\n\
	dir		.2, 0.1, 1.0\n\
	coef	1\n\
}\n\
\n\
\n\
\n\
cone\n\
{\n\
	pos		0, -3, 5\n\
	col		108, 139, 61\n\
	dir		0, 1, 0\n\
	coef	1\n\
}\n\
\n\
\n\
# On eleve tout les comentaire\n\
# On doit trouver des objet avec des parametre (float)\n\
# Il ne sont pas necessairement tous definie\n\
# Il peu y avoir des erreur: truc en trop, mal parametrer\n\
# 	- on met des valeur par default, ou autre chose\n\
#	- il peu y a voir une double definition ... on prend la dernier\n");
	}
	return (str);
}
