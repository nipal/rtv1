# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2017/12/06 17:11:50 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re


# //////////////// cross platforme
OS	:=	$(shell uname -s)
PROC	:= $(shell uname -p)
# ////////////////


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

OBJ			= $(SRC:.c=.o)


LIB_DIR		= -L ../libft  -L ../libft -L ../quaternion
LIB_NAME	=  -lmlx -lquaternion -lft -lm  #-lX11 -lXext

ifeq "$(OS)" "Linux"
LIB_DIR		+=  -L ../minilibx
LIB_NAME	+=  -lX11 -lXext
FRAMEWORK	= 
endif
ifeq "$(OS)" "Darwin"
FRAMEWORK	= -framework OpenGl -framework AppKit
LIB_DIR		+=  -L ../minilibx_macos
endif


all: $(NAME)

$(NAME): $(OBJ)
ifeq "$(OS)" "Darwin"
		@$(CC) $(CFLAGS) -o $(NAME)  $(LIB_DIR)  $(FRAMEWORK) $(LIB_NAME) $(OBJ)
endif
ifeq "$(OS)" "Linux"
		@$(CC) $(CFLAGS) -o $(NAME)  $(LIB_DIR)  $(FRAMEWORK) $(OBJ) $(LIB_NAME)
endif
#		-L /usr/lib/ -lmlx -lm -lX11 -lXext
#

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -o $@ -c $< -I ../inc -I ../minilibx -I ../minilibx_macos 

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
