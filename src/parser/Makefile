# this Makefile is only for test purpose.
# please remove it if you don't need it in your own branch.

NAME = cub3D
FLAGS = -Wall -Wextra -Werror
SRCS = parser.c main.c
OBJ = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ) ../libft/libft.a
#$(FLAGS)

$(OBJ): $(SRCS)
	cc -c  $(SRCS)
#$(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
