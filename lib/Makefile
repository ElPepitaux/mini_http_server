##
## EPITECH PROJECT, 2024
## mini_http_server
## File description:
## Makefile
##

NAME = libmy.a

CFLAGS = -Wall -Werror -Wextra -W

SRC = 	list.c \
		linked_list.c \

OBJ = $(SRC:.c=.o)

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../

clean:
	find -type f -name "#*#" -delete -o \
	-type f -name "*~" -delete -o -type f -name "*.o" -delete -o \
	-type f -name "*.gc*" -delete

fclean: clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re: fclean all
