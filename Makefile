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
		src/manage_client.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -I./include -I./lib -Wall -Wextra -Werror

LDFLAGS = -L./ -lmy

all: mlib $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

tests_run: mlib $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

mlib:
	make -C lib/

DEBUG:
	gcc -o debug $(SRC) $(CFLAGS) lib/*.c -g3 -ggdb

clean:
	rm -f $(OBJ)
	rm -f debug
	make clean -C lib/

fclean: clean
	rm -f $(NAME)
	make fclean -C lib/

re: fclean all
