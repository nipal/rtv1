# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/04 00:00:48 by fjanoty           #+#    #+#              #
#    Updated: 2017/11/01 17:29:26 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean q1ll fclean re

NAME	=	libquaternion.a
DEPS	=	quaternion.h

SRC		=	quaternion.c			\
			quaternion_operator.c	\
			mat3.c					\
			mat3_rot.c				\
			vec3.c					\
			vec3_add_sub.c			\
			vec3_operator.c			\
			vec3_print.c			\

OBJ		= $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o:%.c$(DEPS)
	@$(CC) $(CFLAGS) -c $(SRC) -I .

clean:
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re: fclean all
