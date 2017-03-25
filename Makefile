##
## Makefile for Project-Master in /Users/robinustarroz/rendu/systeme_unix/PSU_2016_lemipc
## 
## Made by ustarr_r
## Login   <ustarr_r@epitech.eu>
## 
## Started on  Sat Mar 25 11:43:14 2017 ustarr_r
## Last update Sat Mar 25 11:45:30 2017 ustarr_r
####

CC	= gcc

RM	= rm -f

CFLAGS	+= -W -Wall -Wextra -Werror

NAME	= lemipc

SRC	= src/main.c

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
