/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:43:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/12 03:49:47 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_parser(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->parser.imgsidewall[i])
		{
			free(game->parser.imgsidewall[i]);
			game->parser.imgsidewall[i] = NULL;
		}
	}
}

static void	free_map(t_game *game)
{
	if (game->map.file)
		ft_freematrix(&game->map.file);
	if (game->map.cpyfile)
		ft_freematrix(&game->map.cpyfile);
	if (game->map.map)
		ft_freematrix(&game->map.map);
}

void	free_all(t_game *game)
{
	free_parser(game);
	free_map(game);
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	game->map.file = NULL;
	game->map.cpyfile = NULL;
	game->map.map = NULL;
}
