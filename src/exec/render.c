/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 23:55:21 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/17 04:10:35 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* static int	rgb_to_int(t_color c)
{
	return ((c.r << 24) | (c.g << 16) | (c.b << 8) | 255);
} */

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, 0x87CEEBFF);
			else
				mlx_put_pixel(game->img, x, y, 0x444444FF);
			x++;
		}
		y++;
	}
}

void	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	player_input(game);
	draw_background(game);
	raycasting(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_TAB))
		draw_map(game);
	//debug por consola
	printf("Posición jugador: x=%f, y=%f\n", game->player.x, game->player.y);
	printf("Dirección jugador: dir_x=%f, dir_y=%f\n", game->player.dir_x, game->player.dir_y);
	usleep(500);
}
