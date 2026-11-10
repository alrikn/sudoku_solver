##
## ALRIK PROJECT, 2026
## sudoku_solver
## File description:
## Makefile
##

CC	=	clang

SRC	=	main.c \
		checks.c \
		possibility.c \
		solver.c \
		table.c

OBJ	= $(SRC:.c=.o)

NAME = sudoku_solver

CPPFLAGS +=	-I./include
CFLAGS	+=	-Wall -Wextra

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

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
