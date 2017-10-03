# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/04 00:00:48 by fjanoty           #+#    #+#              #
#    Updated: 2017/10/04 00:04:47 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean q1ll fclean re

NAME	=	libquaternion.a
DEPS	=	quaternion.h

SRC		=	quaternion.c		\
			vec3.c				\

OBJ		= $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	arrc $(NAME)$(OBJ)
	ranlib $(NAME)

%.o:%.c$(DEPS)
	$(CC) $(CFLAGS) -c $(SRC) -I .

clean:
	rm-f$(OBJ)

fclean : clean
	rm-f$(NAME)

re: fclean all

