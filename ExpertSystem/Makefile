# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/02 20:36:32 by aradiuk           #+#    #+#              #
#    Updated: 2019/03/17 12:08:08 by aradiuk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computor 

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC_FILES = $(shell ls $(SRC_DIR))

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC =	-I inc/

OBJ_FILES = $(SRC_FILES:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

GCC = clang++ -std=c++11 #-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(GCC) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
