/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paularuizalcarazgmail.com <paularuizalc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:08 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/29 20:12:21 by paularuizal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <time.h>
# include <stdio.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

enum dir
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
};

typedef struct s_parser
{
	char	*imgsidewall[4];
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
	char		**map;
	char		**cpymap;
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
	void		*mlx;
	void		*window;
	//t_img		*images;
	//t_txture	*txture;
	t_parser	parser;
	t_map		map;
	t_player	player;
}		t_game;

/* ************************************************************************** */
/*                                  INIT                                      */
/* ************************************************************************** */
void	init_values(t_game *game);
void	init_player(t_game *game);

/* ************************************************************************** */
/*                                  PARSE                                     */
/* ************************************************************************** */
char	**read_map(char *file_map);
void	parse_map(t_game *game, char **map);
void	get_sidetxt(t_game *game, char **map);

/* ************************************************************************** */
/*                                  UTILS                                     */
/* ************************************************************************** */
void	ft_error(char *str);

#endif