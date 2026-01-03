/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:08 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/03 20:55:00 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <time.h>
# include <stdio.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define CELL_SIZE 20
# define PLAYER_SIZE 10

enum dir
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
};

enum rgb
{
	F = 0,
	C = 1,
};

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_parser
{
	char	*imgsidewall[4];
	t_color	rgb[2];
}		t_parser;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}		t_player;

typedef struct s_map
{
	char		**file;
	char		**cpyfile;
	char		**map;
	int			width;
	int			length;
	int			player;
	int			floor;
	int			wall;

	//t_player	player_pos;
	//t_exit		exit_pos;
}		t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	void		*window;
	t_parser	parser;
	t_map		map;
	t_player	player;
}		t_game;

/* ************************************************************************** */
/*                                  INIT                                      */
/* ************************************************************************** */
void	init_values(t_game *game);
void	init_player(t_game *game);
void	init_mlx(t_game *game);

/* ************************************************************************** */
/*                                  PARSE                                     */
/* ************************************************************************** */
char	**read_map(char *file_map);
void	parse_file(t_game *game, char **map);
void	get_sidetxt(t_game *game, char **map);
void	get_colors(t_game *game, char **map);
int		get_type(char *line, char **sides, int len);
char	*get_path(char *line);

/* ************************************************************************** */
/*                                   EXEC                                     */
/* ************************************************************************** */
void	draw_map(t_game *game);

/* ************************************************************************** */
/*                                  UTILS                                     */
/* ************************************************************************** */
void	ft_error(char *str);
void	ft_printrgb(t_game *game);

#endif