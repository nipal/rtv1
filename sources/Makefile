# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2016/12/19 01:26:44 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re

DEPS = ../includes/rtv1.h

SRC		= 	main.c			\
			init_rtv1.c		\
			init_win.c		\
			init_opencl.c	\
			event.c 		\
			hook.c			\
			math_vector.c	\
			error_opencl.c	\
			exit.c 

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS)  -o ../$(NAME) $(OBJ) -L ../libft/ -lft \
		-L ../c_maths -lc_maths \
		-L ../minilibx_macos -lmlx \
		-framework OpenGL -framework AppKit -framework opencl 

#		-L /usr/lib/ -lmlx -lm -lX11 -lXext



%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $< -I ../includes -I ../minilibx_macos

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all
