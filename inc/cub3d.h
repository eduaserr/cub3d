/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:08 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/27 23:09:38 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <time.h>
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
}		t_game;

char	**read_map(char *file_map);

void	init_values(t_game *game);

void	parse_map(t_game *game, char **map);

void	ft_error(char *str);
#endif