/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 23:55:03 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/13 23:55:04 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	check_and_move(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	if (game->map.map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->map.map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
}

void	move(t_game *game, double dir_x, double dir_y)
{
	double	speed;

	speed = game->player.speed;
	check_and_move(game, dir_x * speed, dir_y * speed);
}

/*void	move_forward(t_game *game)
{
	double	speed;

	speed = 0.1;
	if (game->map.map[(int)game->player.y][(int)(game->player.x + game->player.dir_x * speed)] != '1')
		game->player.x += game->player.dir_x * speed;
	if (game->map.map[(int)(game->player.y + game->player.dir_y * speed)][(int)game->player.x] != '1')
		game->player.y += game->player.dir_y * speed;
}

void	move_backward(t_game *game)
{
	double	speed;

	speed = 0.1;
	if (game->map.map[(int)game->player.y][(int)(game->player.x - game->player.dir_x * speed)] != '1')
		game->player.x -= game->player.dir_x * speed;
	if (game->map.map[(int)(game->player.y - game->player.dir_y * speed)][(int)game->player.x] != '1')
		game->player.y -= game->player.dir_y * speed;
}

void	move_left(t_game *game)
{
	double	speed;

	speed = 0.1;
	if (game->map.map[(int)game->player.y][(int)(game->player.x - game->player.plane_x * speed)] != '1')
		game->player.x -= game->player.plane_x * speed;
	if (game->map.map[(int)(game->player.y - game->player.plane_y * speed)][(int)game->player.x] != '1')
		game->player.y -= game->player.plane_y * speed;
}

void	move_right(t_game *game)
{
	double	speed;

	speed = 0.1;
	if (game->map.map[(int)game->player.y][(int)(game->player.x + game->player.plane_x * speed)] != '1')
		game->player.x += game->player.plane_x * speed;
	if (game->map.map[(int)(game->player.y + game->player.plane_y * speed)][(int)game->player.x] != '1')
		game->player.y += game->player.plane_y * speed;
}*/

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

/*
void	player_input(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
*/