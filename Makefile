# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 03:22:17 by eduaserr          #+#    #+#              #
#    Updated: 2026/01/27 16:54:04 by eduaserr         ###   ########.fr        #
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

EXEC	= src/exec/
FREE	= src/free/
INIT	= src/init/
PARSE	= src/parse/
PRINT	= src/print/

### SRCS ###
SRC		= main.c
SRCS	= $(INIT)init.c $(INIT)init_mlx.c $(INIT)init_player.c \
		$(EXEC)draw_map.c \
		$(FREE)free.c \
		$(PARSE)read_map.c $(PARSE)parse_file.c $(PARSE)parse_map.c $(PARSE)find_map.c $(PARSE)map_validation.c $(PARSE)parse_textures.c $(PARSE)parse_colors.c $(PARSE)parse_utils.c \
		$(PRINT)print.c

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