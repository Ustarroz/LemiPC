##
## Makefile for Project-Master in /Users/robinustarroz/rendu/systeme_unix/PSU_2016_lemipc
## 
## Made by ustarr_r
## Login   <ustarr_r@epitech.eu>
## 
## Started on  Sat Mar 25 11:43:14 2017 ustarr_r
## Last update Thu Mar 30 17:16:36 2017 Edouard
####

CC	= gcc

RM	= rm -f

CFLAGS	= -W -Wall -Wextra -Werror
CFLAGS	+= -Iinclude

NAME	= lemipc

SRC	= src/main.c \
	  src/id_manager.c \
	  src/mov_management.c \
	  src/token_management.c

OBJ	= $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
