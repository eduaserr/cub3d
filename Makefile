# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paularuizalcarazgmail.com <paularuizalc    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 03:22:17 by eduaserr          #+#    #+#              #
#    Updated: 2026/01/03 19:56:57 by paularuizal      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
NAME	= cub3d
CC		= clang
CFLAGS	= -Wall -Wextra -Werror -Wunreachable-code -O3 -g
LIBMLX	:= ./lib/MLX42
LIB		:= ./lib/libft

HEADERS	:= -I ./inc -I $(LIBMLX)/include/MLX42
LIBS	:= -L $(LIB) -lft -L $(LIBMLX)/build/ -lmlx42 -ldl -lglfw -pthread -lm
RM		= rm -rf

INIT	= src/init/
PARSE	= src/parse/
EXEC	= src/exec/

### SRCS ###
SRC		= main.c
SRCS	= $(INIT)init.c \
		  $(INIT)init_mlx.c \
		  $(INIT)init_player.c \
		  $(PARSE)read_map.c \
		  $(PARSE)parse_map.c \
		  $(PARSE)parse_textures.c \
		  $(PARSE)parse_colors.c \
		  $(PARSE)parse_utils.c \
		  $(EXEC)draw_map.c \

### OBJS ###
OBJS	= $(SRC:.c=.o) $(SRCS:.c=.o)

### RULES ###
all : libmlx $(NAME)

libmlx:
	$(MAKE) -C $(LIB)
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	@echo "loading cub3d..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "cub3d compiled successfully"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@echo "clearing cub3d...🧹"
	@$(MAKE) -C $(LIB) clean
	@$(RM) $(OBJS) main.o
	@$(RM) $(LIBMLX)/build

fclean: clean
	@$(RM) $(NAME) main
	@$(MAKE) -C $(LIB) fclean
	@echo "clearing cub3d executable"

re: fclean all

.PHONY: all clean fclean re