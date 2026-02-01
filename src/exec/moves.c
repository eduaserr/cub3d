#include "../../inc/cub3d.h"

void	move_forward(t_game *game)
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
	if (game->map.map[(int)game->player.y][(int)(game->player.x - game->player.dir_x * speed)] != '1')
		game->player.x -= game->player.plane_x * speed;
	if (game->map.map[(int)(game->player.y - game->player.dir_y * speed)][(int)game->player.x] != '1')
		game->player.y -= game->player.plane_y * speed;
}

void	move_right(t_game *game)
{
	double	speed;

	speed = 0.1;
	if (game->map.map[(int)game->player.y][(int)(game->player.x + game->player.dir_x * speed)] != '1')
		game->player.x += game->player.plane_x * speed;
	if (game->map.map[(int)(game->player.y + game->player.dir_y * speed)][(int)game->player.x] != '1')
		game->player.y += game->player.plane_y * speed;
}

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
