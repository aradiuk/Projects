# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/02 20:36:32 by aradiuk           #+#    #+#              #
#    Updated: 2018/08/30 19:33:26 by aradiuk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = abstractVM 

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC_FILES = $(shell ls $(SRC_DIR))

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

INC =	-I inc/

OBJ_FILES = $(SRC_FILES:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

GCC = clang++ -Wall -Werror -Wextra -std=c++11

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
