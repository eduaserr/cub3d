/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr < eduaserr@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:43:20 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/10 21:16:10 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_cell(t_game *game, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < CELL_SIZE)
	{
		j = 0;
		while (j < CELL_SIZE)
		{
			mlx_put_pixel(game->img, 20 + x * CELL_SIZE + i, 20 + y * CELL_SIZE + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = 20 + (int)(game->player.x * CELL_SIZE) - PLAYER_SIZE / 2; // Para estar centrado entre las dos paredes
	start_y = 20 + (int)(game->player.y * CELL_SIZE) - PLAYER_SIZE / 2;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			mlx_put_pixel(game->img, start_x + i, start_y + j, 0x0000FFFF);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (game->map.map[j])
	{
		i = 0;
		while (game->map.map[j][i])
		{
			// Es una pared
			if (game->map.map[j][i] == '1')
				draw_cell(game, i, j, 0xFF0000FF);
			else if (game->map.map[j][i] == '0')
				draw_cell(game, i, j, 0x00FF00FF);
			i++;
		}
		j++;
	}
	draw_player(game);
}
