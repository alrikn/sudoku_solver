##
## ALRIK PROJECT, 2026
## sudoku_solver
## File description:
## Makefile
##

CC	=	clang

SRC	=	src/main.c \
		src/grid/checks.c \
		src/grid/table.c \
		src/possibility/possibility.c \
		src/solver/populate.c \
		src/solver/prune.c \
		src/solver/pointing.c \
		src/solver/hidden.c \
		src/solver/confirm.c \
		src/solver/main_loop.c

OBJ	= $(SRC:.c=.o)

NAME = sudoku_solver

CPPFLAGS +=	-I./include
CFLAGS	+=	-Wall -Wextra -g

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

#i will always ignore header ones for now
check_coding_style:	CC = epiclang
check_coding_style:	fclean $(NAME)

debug:	CFLAGS += -g3
debug:	re

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all check_coding_style debug clean fclean re
