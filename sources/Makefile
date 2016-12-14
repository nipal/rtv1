# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2016/12/14 16:26:38 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re

DEPS = ../includes/rtv1.h

SRC		= 	main.c			\
			init_rtv1.c		\
			init_win.c		\
			init_opencl.c	\
			event.c 		\
			exit.c 

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS)  -o ../$(NAME) $(OBJ) -L ../libft/ -lft \
		-L ../c_maths -lc_maths \
		-lmlx -framework OpenGL -framework AppKit -framework opencl 

#		-L /usr/lib/ -lmlx -lm -lX11 -lXext



%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $< -I ../includes

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all
