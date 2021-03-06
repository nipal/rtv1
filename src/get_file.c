/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 20:20:28 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/08 03:36:17 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_list	*create_node(char *str, int size)
{
	t_list	*node;

	if (!(str)
		|| !(node = malloc(sizeof(t_list)))
		|| !(node->str = (char*)malloc(size)))
		return (NULL);
	ft_memmove(node->str, str, size);
	node->size = size;
	node->next = NULL;
	return (node);
}

t_list	*get_lst_str(int *size, int fd)
{
	t_list	*beg;
	t_list	*node;
	char	buff[BUFF_SIZE + 1];
	int		ret;
	int		s;

	beg = NULL;
	if (!size)
		return (NULL);
	s = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!(node = create_node(buff, ret)))
			return (NULL);
		node->next = beg;
		beg = node;
		s += ret;
	}
	if (ret < 0)
		perror("read_error -->");
	*size = s;
	return (beg);
}

void	free_lst(t_list *beg)
{
	t_list	*tmp;
	t_list	*node;

	node = beg;
	while (node)
	{
		tmp = node->next;
		free(node->str);
		free(node);
		node = tmp;
	}
}

char	*get_entry(int fd, int *size)
{
	t_list	*beg;
	t_list	*node;
	char	*str;
	int		i;
	int		max;

	if (!size || !(beg = get_lst_str(size, fd))
		|| !(str = malloc((*size + 1) * sizeof(char))))
		return (NULL);
	ft_memset(str, 0, (*size + 1) * sizeof(char));
	max = (*size / BUFF_SIZE) + ((*size % BUFF_SIZE) != 0);
	i = 0;
	node = beg;
	while (i < max && node)
	{
		ft_memmove(str + (max - i - 1) * BUFF_SIZE, node->str, node->size);
		node = node->next;
		i++;
	}
	free_lst(beg);
	return (str);
}

char	*file_get_str(const char *file_path, int *size)
{
	char	*str;
	int		fd;

	if (!size)
		return (NULL);
	if (((fd = open(file_path, O_RDONLY)) < 0))
	{
		perror(file_path);
		return (NULL);
	}
	if (!(str = get_entry(fd, size)))
	{
		perror("reading file error\n");
		close(fd);
		return (NULL);
	}
	close(fd);
	return (str);
}
