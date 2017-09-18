# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/01 03:02:20 by fjanoty           #+#    #+#              #
#    Updated: 2017/09/18 16:52:13 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re

NAME	=	libvec_math.a
DEPS 	= vec_math.h

SRC		= 	basis.c		\
		  	matrix.c	\
		  	vector.c	\

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS)  -c $(SRC) -I ../inc

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

