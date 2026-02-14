/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:43:20 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/14 12:50:10 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_cell(t_game *game, int x, int y, uint32_t color)
{
	int			i;
	int			j;
	int			screen_x;
	int			screen_y;
	uint32_t	blended_color;

	i = 0;
	while (i < CELL_SIZE)
	{
		j = 0;
		while (j < CELL_SIZE)
		{
			screen_x = 20 + x * CELL_SIZE + i;
			screen_y = 20 + y * CELL_SIZE + j;
			blended_color = blend_pixel(game->img, screen_x, screen_y, color);
			mlx_put_pixel(game->img, screen_x, screen_y, blended_color);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_game *game)
{
	int			i;
	int			j;
	int			start_x;
	int			start_y;
	uint32_t	blended_color;

	start_x = 20 + (int)(game->player.x * CELL_SIZE) - PLAYER_SIZE / 2;
	start_y = 20 + (int)(game->player.y * CELL_SIZE) - PLAYER_SIZE / 2;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			blended_color = blend_pixel(game->img, start_x + i,
					start_y + j, 0xFF0000FF);
			mlx_put_pixel(game->img, start_x + i, start_y + j, blended_color);
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
			if (game->map.map[j][i] == '1')
				draw_cell(game, i, j, 0xFFFFFF88);
			else if (game->map.map[j][i] == '0')
				draw_cell(game, i, j, 0x44444466);
			i++;
		}
		j++;
	}
	draw_player(game);
}
