##
## EPITECH PROJECT, 2024
## mini_http_server
## File description:
## Makefile
##

NAME = mini_http_server

SRC =	src/main.c \
		src/server.c \
		src/get.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -I./include -Wall -Wextra -Werror

all: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

DEBUG:
	gcc -o debug $(SRC) $(CFLAGS) -g3 -ggdb

clean:
	rm -f $(OBJ) 
	rm -f debug

fclean: clean
	rm -f $(NAME)

re: fclean all
