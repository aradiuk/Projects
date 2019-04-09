# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 11:50:38 by aradiuk           #+#    #+#              #
#    Updated: 2019/04/09 14:56:40 by aradiuk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC_FILES = $(shell ls $(SRC_DIR))

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC =	-I inc/ \
		-I ./libft/includes/

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

GCC = gcc -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) ./libft/libft.a
	ar rc $(NAME) $(OBJ)
	rm -rf libft_malloc.so
	ln -s $(NAME) libft_malloc.so 

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(GCC) $(INC) -c $< -o $@

./libft/libft.a:
	make -C libft

clean:
	make clean -C libft
	rm -rf libft_malloc.so
	rm -rf $(OBJ)

fclean: clean
	rm -rf libft/libft.a
	rm -rf libft_malloc.so
	rm -rf $(NAME)

re: fclean all

