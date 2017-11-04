/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rtv1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 18:28:09 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 14:32:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//////////////////////////////////////////////////////////////


//	parsing file structure

int		is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int		is_alphanum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || (c == '_')) 
		return (1);
	return (0);
}


int		skip_withe_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	return (i);
}

int		skip_non_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_space(str[i]))
		i++;
	return (i);
}

/*
**	on cherche un caracter precis apres des with space
*/
int 	find_char(const char *str, char target)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != target && is_space(str[i]))
		i++;
	return (((str[i] == target) ? i + 1: -1));
}

int		find_char_force(const char *str, char target)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != target)
		i++;
	return (((str[i] == target) ? i + 1: -1));
}

int		is_parsing_finnished(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

/*
**	On cherche la taille d'un mots
*/
int	get_word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_alphanum(str[i]))
		i++;
	return (i);
}

// convert txt into value

double	atol_size(const char *str, int *curs)
{
	int		i;
	int		j;
	double		nb;
	double		factor;

	if (curs)
		*curs = 0;
	if (str)
	{
		i = 0;
		factor = 1;
		nb = 0;
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		if (str[i] == 45 || str[i] == 43)
			factor = 44 - str[i++];
		j = 0;
		while (str[i] >= 48 && str[i] <= 57 && ++j < 15)
			nb = nb * 10 + str[i++] - 48;
		if (curs)
			*curs = i;
		return (nb * factor);
	}
	return (0);
}

int	double_is_neg(double nb)
{
	if (*(unsigned long*)(&nb) & (unsigned long)1 << 63)
		return (1);
	return (0);
}

double	str_get_double(const char *str, int *curs)
{
	double 	nb;
	double	coef;
	long	tmp;
	int		i;
	double	sign;

	nb = (double)atol_size(str, &i);
	sign = (double_is_neg(nb)) ? -1.0 : 1.0;
	nb = (double_is_neg(nb)) ? nb * -1 : nb;
	*curs = i;
	if (str[i] && str[i] == '.'  && str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		tmp = atol_size(str + i + 1, &i);
		coef = 1.0 / pow(10, i);
		nb += tmp * coef;
		*curs += i + 1;
	}
	nb *= sign;
//	printf(">>>%.10s<<<	%f\n", str, nb);
	return (nb);
}

//void	test_get_double(const char *str)
//{
//	int	i;
//	
//	printf("%s -> %.20f\n", str, str_get_double(str, &i));
//	printf("%s -> %.20f\n", str, atof(str));
//}

// debug

//void	print_bit(unsigned long toto, int val)
//{
//	char c;
//
//	c = (toto & 1) ? '1': '0';
//	if (++val < 64)
//		print_bit(toto >> 1, val);
//	printf("%c", c);
//}

t_vec3	vec3_null(int i)
{
	static	t_vec3	vec = {0 , 0, 0};

	(void)i;
	return (vec);
}

t_vec3	str_get_vec3(const char *str, int *curs, int *err)
{
	int		add;
	int		i;
	int		coma;
	t_vec3	vec;

	vec.x = str_get_double(str, &i);
	if ((coma = find_char(str + i, ',')) < 0)
		return (vec3_null(*err = -1));
	add = i + coma;
	vec.y = str_get_double(str + add, &i);
	if ((coma = find_char(str + add + i, ',')) < 0)
		return (vec3_null(*err = -1));
	add += i + coma;
	vec.z = str_get_double(str + add, &i);
	*curs = add + i;
	return (vec);
}

//void	print_vec3(t_vec3 vec)
//{
//	printf("x:%f	y:%f	z:%f\n", vec.x, vec.y, vec.z);
//}

void	remove_coment(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
		{
			j = 0;
			while (str[i + j] && str[i + j] != '\n')
				j++;
			ft_memmove(str + i, str + i + j, ft_strlen(str + i + j) + 1);
		}
		i++;
	}
}

/*
**	Il sagit de prendre un mot et dire si quel valeur on incremente
*/


//	obj: 	plan, sphere, cylindre, cone
//	light
//	camera

//void	obj_add_value(t_obj *obj, char *str, int *curs)
//{
//	(void)obj;
//	(void)str;
//	(void)curs;
//}


long		get_asset_offset(int id_assets)
{
	t_obj o;

	if (id_assets == 0)
		return ((long)&o.value - (long)(&o));
	if (id_assets == 1)
		return ((long)&o.pos - (long)(&o));
	if (id_assets == 2)
		return ((long)&o.dir - (long)(&o));
	if (id_assets == 3)
		return ((long)&o.col - (long)(&o));
	if (id_assets == 4)
		return ((long)&o.pow_spec - (long)(&o));
	return (-1);
}

long		get_cam_offset(int id_cam)
{
	t_cam c;

	if (id_cam == 0)
		return ((long)(&c.pos) - (long)(&c));
	if (id_cam == 1)
		return ((long)(&c.uz) - (long)(&c));
	return (-1);
}

long		get_light_offset(int id_light)
{
	t_light l;

	if (id_light == 0)
		return ((long)(&l.pos) - (long)(&l));
	if (id_light == 1)
		return ((long)(&l.col) - (long)(&l));
	return (-1);
}


char	*get_tab(int tab_nb, int *size)
{
	static	char	object_type[][KEY_WORD_SIZE] = {"plan", "sphere", "cylinder", "cone", "light", "camera"};
	static	char	assets_comp[][KEY_WORD_SIZE] = {"value", "pos", "dir", "col", "spec"};
	static	char	cam_comp[][KEY_WORD_SIZE] = {"pos", "dir"};
	static	char	light_comp[][KEY_WORD_SIZE] = {"pos", "col"};

	if (!size)
		return (NULL);
	if (tab_nb == OBJ_TYPE && (*size = (sizeof(object_type) / KEY_WORD_SIZE)))
		return ((char*) object_type);
	if (tab_nb == ASSETS_COMP && (*size = (sizeof(assets_comp) / KEY_WORD_SIZE)))
		return ((char*) assets_comp);
	if (tab_nb == CAM_COMP && (*size = (sizeof(cam_comp) / KEY_WORD_SIZE)))
		return ((char*) cam_comp);
	if (tab_nb == LIGHT_COMP && (*size = (sizeof(light_comp) / KEY_WORD_SIZE)))
		return ((char*) light_comp);
	return (NULL);
}

int		find_id_from_name(char *word, int *add_curs, int tab_id)
{
	int		i;
	int		offset;
	char	*tab_key_word;
	int		size_tab;
	int		size_word;

	if (!add_curs)
		return (-1);
	offset = skip_withe_space(word);
	size_word = get_word_size(word + offset);
	tab_key_word = get_tab(tab_id, &size_tab);
//	printf("size_word:%d\n", size_word);
//	write(1, word + offset, size_word);
//	printf("\n");
//	printf("tab_id:%d	offset:%d	size_word:%d	======>%.10s<=====\n", tab_id, offset, size_word, (word + offset));
	*add_curs += offset + size_word;
	if (size_word <= 0)
	{
		(*add_curs)++;
		return (-1);
	}
	i = 0;
	while (i < size_tab)
	{
		if (!strncmp(tab_key_word + KEY_WORD_SIZE * i, word + offset, size_word))
			return (i);
		i++;
	}
	return (-1);
}

void	parse_error(int id, char *str)
{
	ft_putstr("parse error	");
	ft_putnbr(id);
	ft_putstr(":	txt==>");
	ft_putstr(str);
	ft_putstr("<==\n");
	exit(0);
}

/*
# define OBJ_TYPE 		0
# define ASSETS_COMP	1
# define CAM_COMP		2
# define LIGHT_COMP		3
*/

//typedef	struct	s_entities
//{
//	int					type;				// assets:0, light:1, cam:2
//	int					sub_type;			// if assets:[0-4] else:0
//	void				*entities;			//
//	struct	s_entities	*next;
//}				t_entities;

void	entities_push(t_entities **beg, t_entities *new_elem)
{
	if (!beg || !new_elem)
		return ;
	new_elem->next = *beg;
	*beg = new_elem;
}

t_entities	*entities_create(void *data, int id)
{
	t_entities	*new_elem;

	if (!data || !(new_elem = (t_entities*)malloc(sizeof(t_entities))))
	{
		return (NULL);
	}
	if (id >= 0 && id <= 3)	
	{
		new_elem->type = 0;
		new_elem->sub_type = id;
	}
	else
	{
		new_elem->type = (id == 4) ? 1: 2;
		new_elem->sub_type = 0;
	}
	new_elem->entities = data;
	new_elem->next = NULL;
	return (new_elem);
}

void	entities_destroy(t_entities *elem)
{
	t_entities *tmp;

	while (elem)
	{
		tmp = elem->next;
		free(elem);
		elem = tmp;
	}
}

void	asset_comp_fill(char *str, int *add_curs, t_obj *obj, int id_comp)
{
	int		i;
	int		err;

	i = 0;
//printf("id_comp:%d\n", id_comp);
	if (id_comp == 0 || id_comp == 4)
	{
		(*(double*)((long)obj + (long)get_asset_offset(id_comp))) = str_get_double(str, &i);
	}
	else
		(*(t_vec3*)((long)obj + (long)get_asset_offset(id_comp))) = str_get_vec3(str, &i, &err);
	*add_curs += i;
}

void	color_range(t_vec3 *col)
{
	if (col->x < 0)
		col->x = 0;
	if (col->y < 0)
		col->y = 0;
	if (col->z < 0)
		col->z = 0;
	if (col->x > 255)
		col->x = 255;
	if (col->y > 255)
		col->y = 255;
	if (col->z > 255)
		col->z = 255;
}

void	asset_finish(t_obj *obj, int comp)
{
	double	coef;

	if (!obj)
		return ;
	if (!(comp & 1))
		obj->value = 1;
	if (!(comp & 2))
		obj->pos = vec3_set(0, 0, 0);
	if (!(comp & 4))
		obj->dir = vec3_normalise(vec3_set(1, -1, -1));
	if (!(comp & 8))
		obj->col = vec3_set(200, 200, 200);
	if (!(comp & 8))
		obj->pow_spec = 0;
	color_range(&obj->col);
	if (obj->type == CONE)
	{
		coef = tan(obj->value * M_PI / 180.0); 
		obj->value = coef * coef;
	}
	else
		obj->value = fabs(obj->value);
}

t_obj	*get_assets(char *str, int id, int *add_curs)
{
	t_obj	*obj;
	int		size;
	int		id_comp;
	int		i;
	int		comp;
	
	if (!add_curs || !(obj = (t_obj*)malloc(sizeof(t_obj))))
		return (NULL);
	size = find_char_force(str, '}');
	i = 0;
	comp = 0;
	obj->type = id;
	id_comp = -1;
	while (i < size - 1)
	{
		if ((id_comp = find_id_from_name(str + i, &i, ASSETS_COMP)) >= 0)
		{
			comp |= 1 << id_comp;
			asset_comp_fill(str + i, &i, obj, id_comp);
		}
	}
	*add_curs += size;
	asset_finish(obj, comp);
	return (obj);
}


void	light_finish(t_light *light, int comp)
{
	if (!light)
		return ;
	if (!(comp & 1))
		light->pos = vec3_set(0, 0, 0);
	if (!(comp & 2))
		light->col = vec3_set(255, 255, 255);
	color_range(&light->col);
}

void	light_comp_fill(char *str, int *add_curs, t_light *light, int id_comp)
{
	int		i;
	int		err;

	i = 0;
	(*(t_vec3*)((long)light + (long)get_light_offset(id_comp))) = str_get_vec3(str, &i, &err);
	*add_curs += i;
}


t_light	*get_light(char *str, int id, int *add_curs)
{
	(void)id;
	t_light	*light;
	int		size;
	int		id_comp;
	int		i;
	int		comp;
	
	if (!add_curs || !(light = (t_light*)malloc(sizeof(t_light))))
		return (NULL);
	size = find_char_force(str, '}');
	i = 0;
	comp = 0;
	while (i < size - 1)
	{
		if ((id_comp = find_id_from_name(str + i, &i, LIGHT_COMP)) >= 0)
		{
			comp |= 1 << id_comp;
			light_comp_fill(str + i, &i, light, id_comp);
		}
	}
	*add_curs += size;
	light_finish(light, comp);
	return (light);
}


void	cam_finish(t_cam *cam, int comp)
{
	if (!cam)
		return ;
	if (!(comp & 1))
		cam->pos = vec3_set(0, 0, -15);
	if (!(comp & 2))
		cam->uz = vec3_set(0, 0, 1);
	if (!(comp & 4))
		cam->uy = vec3_set(0, 1, 0);
}

void	cam_comp_fill(char *str, int *add_curs, t_cam *cam, int id_comp)
{
	int		i;
	int		err;

	i = 0;
	(*(t_vec3*)((long)cam + (long)get_cam_offset(id_comp))) = str_get_vec3(str, &i, &err);
	*add_curs += i;
}


t_cam	*get_cam(char *str, int id, int *add_curs)
{
	(void)id;
	t_cam	*cam;
	int		size;
	int		id_comp;
	int		i;
	int		comp;
	
	if (!add_curs || !(cam = (t_cam*)malloc(sizeof(t_cam))))
		return (NULL);
	size = find_char_force(str, '}');
	i = 0;
	comp = 0;
	while (i < size - 1)
	{
		if ((id_comp = find_id_from_name(str + i, &i, CAM_COMP)) >= 0)
		{
			comp |= 1 << id_comp;
			cam_comp_fill(str + i, &i, cam, id_comp);
		}
	}
	*add_curs += size;
	cam_finish(cam, comp);
	return (cam);
}

t_entities	*get_entities(char *file_str)
{
	int	i;
	int	id_obj;
	t_entities	*beg;
	t_entities	*node;

	beg = NULL;
	remove_coment(file_str);
	i = 0;
	while (!is_parsing_finnished(file_str + i))
	{
		if ((id_obj = find_id_from_name(file_str + i, &i, OBJ_TYPE)) < 0)
			parse_error(-1, "no obj_name found");
		if ((i += find_char(file_str + i, '{')) < 0) 
			parse_error(-2, "no begin obj found");
		if (id_obj <= 3)
			node = entities_create(get_assets(file_str + i, id_obj, &i), id_obj);
		else if (id_obj == 4)
			node = entities_create(get_light(file_str + i, id_obj, &i), id_obj);
		else if (id_obj == 5)
			node = entities_create(get_cam(file_str + i, id_obj, &i), id_obj);
		entities_push(&beg, node);
	}
	return(beg);
}

int		item_obj_alloc(t_entities *node, t_item *item)
{
	if (!node || !item)
		return (0);
	item->nb_light = 0;
	item->nb_obj = 0;
	item->nb_cam = 0;
	while (node)
	{
		if (node->type == 0)
			item->nb_obj++;
		else if (node->type == 1)
			item->nb_light++;
		else if (node->type == 2)
			item->nb_cam++;
		node = node->next;
	}
	if (!(item->obj = (t_obj*)malloc(sizeof(t_obj) * item->nb_obj))
		|| !(item->light = (t_light*)malloc(sizeof(t_light) * item->nb_light))
		|| !(item->cam = (t_cam*)malloc(sizeof(t_cam) * item->nb_cam)))
		return (0);
	return (1);
}

void		item_finish_plan(t_obj *plan)
{
	if (vec3_norme((plan->dir = vec3_normalise(plan->dir))) != 1)
		plan->dir = vec3_set(0, 1, 0);
	plan->value = -vec3_dot(plan->dir, plan->pos);
}

void		obj_manage_rot(t_obj *obj)
{
	t_vec3	ang;

	ang = vec3_cartesien_spherique(obj->dir);


	obj->rot_inv = mat3_rot_all(-ang.x, -ang.y, 0);
}

void		item_fill_assets(t_entities *node, t_item *item)
{
	int		i;
	t_obj	obj;

	i = 0;
	while (node)
	{
		if (node->type == TYPE_ASSET)
		{
			obj = *((t_obj*)(node->entities));
			if ((float)vec3_norme((obj.dir = vec3_normalise(obj.dir))) != 1)
				obj.dir = vec3_set(0, 1, 0);
			if (node->sub_type == PLAN)
				obj.value = -vec3_dot(obj.dir, obj.pos);
			if (node->sub_type == CYLINDER || node->sub_type == CONE)
				obj_manage_rot(&obj);
			item->obj[i++] = obj;
		}
		node = node->next;
	}
}

void		item_fill_cam(t_entities *node, t_item *item)
{
	int		i;
	t_cam	cam;

	i = 0;
	while (node)
	{
		if (node->type == TYPE_CAM)
		{
			cam = *((t_cam*)(node->entities));
			if ((float)vec3_norme((cam.uz = vec3_normalise(cam.uz))) != 1)
				cam.uz = vec3_set(0, 0, 1);
			if (cam.uz.x == 0 && cam.uz.z == 0) 
				cam.uy = vec3_set(0, 0, -1); 
			else if (cam.uz.y == 0)	
				cam.uy = vec3_set(0, 1, 0);
			else
				cam.uy = vec3_normalise(vec3_add(vec3_set(0, -vec3_dot(cam.uz, cam.uz) / cam.uz.y, 0), cam.uz));
			cam.ux = vec3_normalise(vec3_cross(cam.uy, cam.uz));
			item->cam[i++] = cam;
		}
		node = node->next;
	}
}

void		item_fill_light(t_entities *node, t_item *item)
{
	int	i;

	i = 0;
	while (node)
	{
		if (node->type == TYPE_LIGHT)
		{
			item->light[i++] = *((t_light*)(node->entities));
		}
		node = node->next;
	}
}

void	item_fill(t_entities *beg, t_item *item)
{
	item_fill_light(beg, item);
	item_fill_cam(beg, item);
	item_fill_assets(beg, item);
}
