# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:28:32 by fjanoty           #+#    #+#              #
#    Updated: 2017/10/07 14:24:53 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re gdb

# -g -fsanitize=address 
# -Ofast
#  -Wall -Wextra -Werror
#export CFLAGS	= -g -fsanitize=address -Wall -Wextra -Werror
export CFLAGS	= -O2 -Werror -Wall -Wextra
#export CFLAGS	= -g3 #-Wall -Wextra

#-fsanitize=address
export CC	= gcc

#-g -fsanitize=address


NAME			= rtv1
SRC_DIR			= ./src
LIB_FT			= ./libft
LIB_VM			= ./vec_math
#LIB_MLX			= ./minilibx
LIB_QUATER		= ./quaternion
LIB_MLX			= ./minilibx_macos

all:
	make -C $(LIB_MLX)
	make -C $(LIB_FT)
	make -C $(LIB_QUATER)
	make -C $(LIB_VM)
	make -C $(SRC_DIR)
	

clean:
	make -C $(LIB_FT)  		clean
	make -C $(LIB_QUATER)	clean
	make -C $(LIB_VM)  		clean
	make -C $(SRC_DIR) 		clean

fclean: clean
	make -C $(LIB_FT)		fclean
	make -C $(LIB_QUATER)	fclean
	make -C $(LIB_VM)		fclean
	make -C $(SRC_DIR)		fclean

re: fclean all
