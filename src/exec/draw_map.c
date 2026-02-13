/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:43:20 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/14 00:38:07 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static uint32_t	blend_alpha(uint32_t fg, uint32_t bg)
{
	uint8_t	alpha;
	uint8_t	inv_alpha;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	alpha = fg & 0xFF;
	inv_alpha = 255 - alpha;
	r = ((((fg >> 24) & 0xFF) * alpha) + (((bg >> 24) & 0xFF) * inv_alpha)) / 255;
	g = ((((fg >> 16) & 0xFF) * alpha) + (((bg >> 16) & 0xFF) * inv_alpha)) / 255;
	b = ((((fg >> 8) & 0xFF) * alpha) + (((bg >> 8) & 0xFF) * inv_alpha)) / 255;
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

static uint32_t	get_pixel(mlx_image_t *img, int x, int y)
{
	uint8_t	*pixel;

	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return (0x000000FF);
	pixel = &img->pixels[(y * img->width + x) * 4];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

static void	draw_cell(t_game *game, int x, int y, uint32_t color)
{
	int			i;
	int			j;
	int			screen_x;
	int			screen_y;
	uint32_t	bg_color;
	uint32_t	final_color;

	i = 0;
	while (i < CELL_SIZE)
	{
		j = 0;
		while (j < CELL_SIZE)
		{
			screen_x = 20 + x * CELL_SIZE + i;
			screen_y = 20 + y * CELL_SIZE + j;
			bg_color = get_pixel(game->img, screen_x, screen_y);
			final_color = blend_alpha(color, bg_color);
			mlx_put_pixel(game->img, screen_x, screen_y, final_color);
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
	uint32_t	bg_color;
	uint32_t	final_color;

	start_x = 20 + (int)(game->player.x * CELL_SIZE) - PLAYER_SIZE / 2;
	start_y = 20 + (int)(game->player.y * CELL_SIZE) - PLAYER_SIZE / 2;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			bg_color = get_pixel(game->img, start_x + i, start_y + j);
			final_color = blend_alpha(0xFF0000FF, bg_color);
			mlx_put_pixel(game->img, start_x + i, start_y + j, final_color);
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
