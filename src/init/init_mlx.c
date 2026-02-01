/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paularuizalcarazgmail.com <paularuizalc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:43:41 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/01 01:00:11 by paularuizal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_textures(t_game *game)
{
	game->tex[NORTH] = mlx_load_png(game->parser.imgsidewall[NORTH]);
	game->tex[SOUTH] = mlx_load_png(game->parser.imgsidewall[SOUTH]);
	game->tex[EAST] = mlx_load_png(game->parser.imgsidewall[EAST]);
	game->tex[WEST] = mlx_load_png(game->parser.imgsidewall[WEST]);
	if (!game->tex[NORTH] || !game->tex[SOUTH] || !game->tex[EAST] || !game->tex[WEST])
		ft_error("Texture load failed");
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		ft_error("MLX init failed");
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		ft_error("Image MLX creation failed");
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, render, game);
}
