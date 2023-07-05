# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#              #
#    Updated: 2023/07/05 14:24:05 by asarikha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$I

RM = /bin/rm -f
RMDIR = /bin/rmdir -p

LIBFT = libft/libft.a

S = src
O = obj
I = includes

FILES = main\
	validate\
	end\
	render\
	mini_map\
	ray_calculate\
	event
	


HEADER = cub3D.h libft.h mlx.h get_next_line.h render.h
HEADER := $(addprefix $I/,$(HEADER))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name '$(FILE).c'))
OBJS = $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS = $(dir $(OBJS))

# Minilibx
MLX_PATH	= mlx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)
MLX_LNK	= -L ./mlx -lmlx -framework OpenGL -framework AppKit

NAME = cub3D

### RULES ###
all: $(MLX) $(LIBFT) $(NAME)

$O/%.o: $S/%.c $(HEADER)
	@mkdir -p $(O_DIRS)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS)
	@echo "Compiling cub3D..."
	@$(CC) $(CFLAGS) $(MLX) $(MLX_LNK) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(COLOUR_GREEN) $(NAME) created$(COLOUR_END)"

### MLX
$(MLX):
	@echo "Making MiniLibX..."
	@make -sC $(MLX_PATH)
	@echo "$(COLOUR_GREEN) $(MLX) created$(COLOUR_END)"

### LIBFT

libft: $(LIBFT)

$(LIBFT):
	@echo "Making libft..."
	@$(MAKE) -C libft
	@echo "$(COLOUR_GREEN) $(LIBFT) created$(COLOUR_END)"

### CLEANING

clean:
	@cd libft && $(MAKE) clean
	@echo "$(COLOUR_RED) $(LIBFT) removed$(COLOUR_END)"
	@$(RM) $(OBJS)
	@if [ -d $O ]; then $(RM) -rf $(O_DIRS) $O; fi

fclean : clean
	@cd libft && $(MAKE) fclean
	@$(RM) $(NAME)
	@echo "$(COLOUR_RED) $(NAME) removed$(COLOUR_END)"

re: fclean $(NAME)

.PHONY: all clean fclean re
