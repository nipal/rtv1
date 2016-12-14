# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:28:32 by fjanoty           #+#    #+#              #
#    Updated: 2016/12/14 02:03:30 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re gdb

#-g -fsanitize=address 
export CFLAGS	= -Wall -Wextra -Werror  -Ofaste

#-fsanitize=address
export CC	= gcc

#-g -fsanitize=address


export NAME			= rt_v1
SRC_DIR			= ./sources
LIB_FT			= ./libft
LIB_M			= ./c_maths

all:
	make -C $(LIB_FT)
	make -C $(LIB_M)
	make -C $(SRC_DIR)

clean:
	make -C $(LIB_FT)  clean
	make -C $(LIB_M)  clean
	make -C $(SRC_DIR) clean

fclean:
	make -C $(LIB_FT)  fclean
	make -C $(LIB_M)  fclean
	make -C $(SRC_DIR) fclean

re: fclean all

lib :
	make -C $(LIB_FT)
	make -C $(LIB_M)

lib_clean:
	make -C $(LIB_FT)	clean
	make -C $(LIB_M)	clean

lib_fclean:
	make -C $(LIB_FT)	   fclean
	make -C $(LIB_M)	   fclean

lib_re: lib_fclean lib

src :
	make -C $(SRC_DIR) 

src_clean:
	make -C $(SRC_DIR) clean

src_fclean: 
	make -C $(SRC_DIR) fclean

src_re: src_fclean src
