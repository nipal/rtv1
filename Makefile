# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:28:32 by fjanoty           #+#    #+#              #
#    Updated: 2017/09/26 20:36:58 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re gdb

# -g -fsanitize=address 
# -Ofast
#  -Wall -Wextra -Werror
export CFLAGS	= -g -fsanitize=address -Wall -Wextra -Werror
#export CFLAGS	= -O3 -Werror #-Wall -Wextra
#export CFLAGS	= -g3 #-Wall -Wextra

#-fsanitize=address
export CC	= gcc

#-g -fsanitize=address


NAME			= rtv1
SRC_DIR			= ./src
LIB_FT			= ./libft
LIB_VM			= ./vec_math
LIB_MLX			= ./minilibx_macos

all:
	make -C $(LIB_MLX)
	make -C $(LIB_FT)
	make -C $(LIB_VM)
	make -C $(SRC_DIR)

clean:
	make -C $(LIB_FT)  clean
	make -C $(LIB_VM)  clean
	make -C $(SRC_DIR) clean

fclean: clean
	make -C $(LIB_FT)  fclean
	make -C $(LIB_VM)  fclean
	make -C $(SRC_DIR) fclean

re: fclean all
