##
## EPITECH PROJECT, 2018
## Project malloc
## File description:
## Build malloc binary.
##

SRC =   rnb_trees/rnb_trees.c \
        rnb_trees/violation.c \
        sources/bit_table_operation.c \
        sources/free_realloc.c \
        sources/match_function.c \
        sources/malloc.c

OBJ	    =   $(SRC:.c=.o)

CFLAGS	=   -Werror -Wextra -W -Wall -Wparentheses -Wsign-compare -Wpointer-sign -Wuninitialized -Wunused-but-set-variable -fPIC -Iincludes/

NAME    =   libmy_malloc.so

CC	=   gcc

all:    $(NAME)

$(NAME):   $(OBJ)
		$(CC) -o $(NAME) $(OBJ) -shared

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

docker:
	sudo docker run -it -v `pwd`:/home/epitest -w /home/epitest epitechcontent/epitest-docker /bin/bash

re: fclean all
