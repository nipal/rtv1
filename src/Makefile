# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2017/10/11 10:26:59 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re

#-fsanitize=address -g3
NAME	=	../rtv1
DEPS = ../inc/rtv1.h ../inc/vec_math.h ../inc/key_linux.h ../inc/key_mac.h

SRC		= 						\
			cam.c				\
			event.c				\
			exit.c				\
			item.c				\
			main.c				\
			mlx_win.c			\
			parse_rtv1.c		\
			get_file.c			\
			test.c				\
			test_parsing.c		\
								\
			object.c			\


OBJ			= $(SRC:.c=.o)


LIB_DIR		= -L ../libft -L ../vec_math -L ../libft -L ../quaternion -L ../minilibx_macos

LIB_NAME	= -lvec_math -lmlx -lft -lquaternion -lm #-lX11 -lXext

FRAMEWORK	= -framework OpenGl -framework AppKit #-framework opencl

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_DIR) $(LIB_NAME) $(FRAMEWORK) 
#		-L /usr/lib/ -lmlx -lm -lX11 -lXext
#

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $< -I ../inc -I ../vec_math

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
