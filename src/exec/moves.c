/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 23:55:03 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/16 23:19:24 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	validate_move(t_game *game, double x, double y, double margin)
{
	if (game->map.map[(int)(y + margin)][(int)(x + margin)] == '1')
		return (0);
	if (game->map.map[(int)(y + margin)][(int)(x - margin)] == '1')
		return (0);
	if (game->map.map[(int)(y - margin)][(int)(x + margin)] == '1')
		return (0);
	if (game->map.map[(int)(y - margin)][(int)(x - margin)] == '1')
		return (0);
	return (1);
}

static void	check_and_move(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;
	double	margin;

	margin = 0.2;
	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	if (validate_move(game, new_x, new_y, margin))
	{
		game->player.x = new_x;
		game->player.y = new_y;
		return ;
	}
	if (validate_move(game, game->player.x, new_y, margin))
		game->player.y = new_y;
	if (validate_move(game, new_x, game->player.y, margin))
		game->player.x = new_x;
}

void	move(t_game *game, double dir_x, double dir_y)
{
	double	speed;

	speed = game->player.speed;
	check_and_move(game, dir_x * speed, dir_y * speed);
}

void	player_input(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move(game, game->player.dir_x, game->player.dir_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move(game, -game->player.dir_x, -game->player.dir_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move(game, -game->player.plane_x, -game->player.plane_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move(game, game->player.plane_x, game->player.plane_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
