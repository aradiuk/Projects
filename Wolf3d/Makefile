# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 11:50:38 by aradiuk           #+#    #+#              #
#    Updated: 2017/04/19 15:44:56 by aradiuk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d  

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC_FILES = $(shell ls $(SRC_DIR))

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC =	-I includes/ \
		-I ./libft/includes/ \
		-I ./libmlx

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

GCC = gcc #-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) ./libft/libft.a
	$(GCC) $(OBJ) -L./libmlx -lmlx -L./libft/ -lft -lm -lXext -lX11 -o $(NAME)

./libft/libft.a:
	make -C libft

$(OBJ_DIR)%.o : $(SRC_DIR)%.c includes/wolf3d.h
	$(GCC) $(INC) -c $< -o $@

clean:
	make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME)

re: fclean all

