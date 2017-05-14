# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 11:50:38 by aradiuk           #+#    #+#              #
#    Updated: 2017/03/25 13:55:18 by aradiuk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC_FILES = $(shell ls $(SRC_DIR))

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC =	-I includes/ \
		-I ./libft/includes/ \
		-I ./minilibx/

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

GCC = gcc -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) ./libft/libft.a
	$(GCC) $(OBJ) -L./libft/ -lft -L./minilibx/ -lmlx -lXext -lX11 -lm -o $(NAME)

./libft/libft.a:
	make -C libft

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(GCC) $(INC) -c $< -o $@

clean:
	make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME)

re: fclean all

