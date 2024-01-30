##
## EPITECH PROJECT, 2024
## mini_http_server
## File description:
## Makefile
##

NAME = mini_http_server

SRC =	src/main.c

OBJ = $(SRC:.c=.o)

CFLAGS = -I./include -Wall -Wextra -Werror

all: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
