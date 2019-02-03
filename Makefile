##
## EPITECH PROJECT, 2018
## Project malloc
## File description:
## Build malloc binary.
##

SRC =   rnb_trees/rnb_trees.c \
        rnb_trees/rnb_violation.c \
        rnb_trees/rnb_alloc.c \
        rnb_trees/rnb_chield.c \
        rnb_trees/rnb_colorflip.c \
        rnb_trees/rnb_dump.c \
        rnb_trees/rnb_family.c \
        rnb_trees/rnb_match.c \
        rnb_trees/rnb_min_max.c \
        rnb_trees/rnb_rotation.c \
        rnb_trees/rnb_swap.c \
        rnb_trees/rnb_consecutive_red.c \
		rnb_trees/rnb_fix_violations.c \
		rnb_trees/rnb_shape.c \
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
