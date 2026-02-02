/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:43:41 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/02 17:49:10 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		game->tex[i] = mlx_load_png(game->parser.imgsidewall[i]);
	if (!game->tex[NORTH] || !game->tex[SOUTH] || !game->tex[EAST] || !game->tex[WEST])
		return (free_all(game), ft_error("Texture load failed"));
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (free_all(game), ft_error("MLX init failed"));
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		return (free_all(game), ft_error("Image MLX creation failed"));
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, render, game);
}
