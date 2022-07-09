# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 22:14:07 by rfelipe-          #+#    #+#              #
#    Updated: 2022/07/09 00:56:32 by rfelipe-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
FLAGS = -g -Wall -Wextra -Werror
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck -q ./philo

INCLUDE_DIR = ./includes
INCLUDE = $(INCLUDE_DIR)/philosophers.h

OBJ_DIR = ./objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_DIR = ./src
SRC = $(SRC_DIR)/philosophers.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/philosophy.c \
	$(SRC_DIR)/checker_utils.c

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling project...\n"
	@$(CC) $(OBJ) -o $(NAME) -pthread
	@echo "Philosophers compiled!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(FLAGS) -I$(INCLUDE_DIR) -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Deleting EVERYTHING...\n"
	@rm -rf $(NAME)
	@echo "Project cleaned up!"

re: fclean all

valgrind: all
	@$(VALGRIND)

v: valgrind
