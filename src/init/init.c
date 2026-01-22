/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:12 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/16 02:04:09 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_mlx_window(t_game *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->img = NULL;
}

static void	init_parser_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		game->parser.imgsidewall[i] = NULL;
}

static void	init_parser_rgb(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		game->parser.rgb[i].r = -1;
		game->parser.rgb[i].g = -1;
		game->parser.rgb[i].b = -1;
	}
}

static void	init_plyr(t_game *game)
{
	ft_bzero(&game->player, sizeof(t_player));
}

void	init_values(t_game *game)
{
	init_mlx_window(game);
	ft_bzero(&game->map, sizeof(t_map));
	init_parser_textures(game);
	init_parser_rgb(game);
	init_plyr(game);
}
