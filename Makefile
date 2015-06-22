# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 14:10:51 by kperreau          #+#    #+#              #
#    Updated: 2015/06/22 17:35:10 by nverdonc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = game

# Dir vars

SRCDIR = src

INCLUDESDIR = includes

# Files vars

MAIN = main.cpp

CFILES = Entity.class.cpp Interface.class.cpp Env.class.cpp Enemy.class.cpp Player.class.cpp Bullets.class.cpp Collision.class.cpp

SRC = $(patsubst %, $(SRCDIR)/%, $(CFILES))

OBJ = $(SRC:.cpp=.o) $(MAIN:.cpp=.o)

HFILES = Entity.class.hpp Env.class.hpp Interface.class.hpp Enemy.class.hpp Player.class.hhp Bullets.class.hpp Collision.class.hpp

HEADERS = $(patsubst %, $(INCLUDESDIR)/%, $(HFILES))

# COMPILATION

ERRORFLAGS = -Wall -Werror -Wextra

INCLUDEFLAGS = -I $(INCLUDESDIR)/

LIB = -lncurses

FLAGS = $(ERRORFLAGS) $(INCLUDEFLAGS)

CC = clang++

# Rules

all: $(NAME)

$(NAME): $(OBJ)
			@$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

re: fclean all

clean:
			@rm -f $(OBJ)

fclean: clean
			@rm -f $(NAME)

%.o: %.c
			@$(CC) -o $@ -c $< $(FLAGS)