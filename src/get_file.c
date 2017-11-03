/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 20:20:28 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/03 18:27:55 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

# define BUFF_SIZE 10

typedef struct	s_list
{
	int				size;
	char			*str;
	struct	s_list	*next;
}				t_list;

t_list	*create_node(char *str, int size)
{
	t_list	*node;
	size_t	size_mem;
	
	if (!(str)
		|| !(node = malloc(sizeof(t_list)))
		|| !(node->str = (char*)malloc((2 * BUFF_SIZE + 1) * sizeof(char))))
		return (NULL);
	size_mem =  ft_strlen(str);
	ft_memmove(node->str, str, size_mem);
	node->size = size;
	node->next = NULL;
	return (node);
}

void	push_front(t_list **beg, t_list *node)
{
	node->next = *beg;
	*beg = node;
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
		push_front(&beg, node);
//		ft_bzero(buff, (BUFF_SIZE + 1) * sizeof(char));
		s += ret;
	}
	if (ret < 0)
	{
		perror("read_error -->\n");
	}
	*size = s + BUFF_SIZE;
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

void	print_lst(t_list *beg)
{
	printf("%d\n", beg->size);
	if (beg->next)
		print_lst(beg->next);
	printf("%s", beg->str);
}

char	*get_entry(int fd, int *size)
{
	t_list	*beg;
	t_list	*node;
	char	*str;
	int	i;
	int	max;
	int	count = 0;
	
	if (!size || !(beg = get_lst_str(size, fd))
			|| !(str = malloc((*size + 1) * sizeof(char))))
		return (NULL);
	ft_memset(str, 0, (*size + 1) * sizeof(char));
	max = (*size / BUFF_SIZE) + ((*size % BUFF_SIZE) != 0);
	printf("MAX:%d		all_size:%d\n", max, *size);
	i = 0;
	node = beg;
	while (i < max && node)
	{
//		printf("i:%d	max:%d\n", i, max);
		count += node->size;
//		printf("\n\n=>%s<=		size:%d	nb_buff:%d/%d\n\n\n", node->str, node->size, i, max);
//		write(1, str + ((max - i - 1) * BUFF_SIZE), node->size);
		ft_memmove(str + ((max - i - 1) * BUFF_SIZE), node->str, node->size);
		node = node->next;
		i++;
	}
	free_lst(beg);
	return (str);
}

char	*file_get_str(const char *file_path, int *size)
{
	char 	*str;
	int		fd;
	
	if (!size)
	{
		printf("yo_1\n");
		return (NULL);
	}
	if (((fd = open(file_path, O_RDONLY)) < 0))
	{
		printf("yo_2\n");
		perror(file_path);
		return (NULL);
	}
	if (!(str = get_entry(fd, size)))
	{
		printf("yo_3\n");
		printf("reading file error\n");
		close(fd);
		return (NULL);
	}
	close(fd);
	return (str);
}
