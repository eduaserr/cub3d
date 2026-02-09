/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:43:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/08 18:03:12 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_img(t_game *game)
{
	if (game->mlx && game->img)
		mlx_delete_image(game->mlx, game->img);
}

void	free_tex(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->mlx && game->tex[i])
		{
			mlx_delete_texture(game->tex[i]);
			game->tex[i] = NULL;
		}
	}
}

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
	if (game->map.map)
		ft_freematrix(&game->map.map);
}

void	free_all(t_game *game)
{
	free_parser(game);
	free_map(game);
	free_tex(game);
	free_img(game);
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	game->map.file = NULL;
	game->map.map = NULL;
}
