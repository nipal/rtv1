# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2017/11/08 06:48:49 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re

#-fsanitize=address -g3
NAME	=	../rtv1
DEPS =  ../inc/rtv1.h

SRC		= 							\
			cam.c					\
			cam_move.c				\
			cam_turn.c				\
			event.c					\
			event_not_use_yet.c		\
			exit.c					\
			get_file.c				\
			item.c					\
			lst.c					\
			lst_map.c				\
			lst_remove_node.c		\
			main.c					\
			mlx_win.c				\
			object.c				\
			object_dist.c			\
			object_dist_all.c		\
			object_normale.c		\
			parse_asset.c			\
			parse_cam.c				\
			parse_entities_lst.c	\
			parse_is_function.c		\
			parse_item_fill.c		\
			parse_key_word.c		\
			parse_light.c			\
			parse_rtv1.c			\
			parse_str_get.c			\
			parse_str_move.c		\
			post_processing.c		\
			post_porcessing_draw.c	\
			ray.c					\
			ray_color.c				\
			ray_geo.c				\
			ray_condition.c			\
			segment.c				\
			print_vec.c				\

OBJ			= $(SRC:.c=.o)


LIB_DIR		= -L ../libft  -L ../quaternion

#LIB_DIR	+= -L ../minilibx_macos
#LIB_DIR		+= -L /usr/lib/
LIB_DIR		+= -L ../minilibx


LIB_NAME	= -lft -lm -lmlx -lquaternion
#LIB_NAME	+= -lmlx
LIB_NAME	+= -lX11 -lXext

#FRAMEWORK	= -framework OpenGl -framework AppKit #-framework opencl
FRAMEWORK	= #-framework OpenGl -framework AppKit #-framework opencl
-fsanitize=address
LIB_NAME	+= $(FRAMEWORK)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME)  $(OBJ)  $(LIB_DIR) $(LIB_NAME)
#		-L /usr/lib/ -lmlx -lm -lX11 -lXext
#

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $< -I ../inc 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
