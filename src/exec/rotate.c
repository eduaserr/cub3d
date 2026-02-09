#include "../../inc/cub3d.h"

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	speed = 0.075;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(speed) - game->player.dir_y * sin(speed);
	game->player.dir_y = old_dir_x * sin(speed) + game->player.dir_y * cos(speed);

	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(speed) - game->player.plane_y * sin(speed);
	game->player.plane_y = old_plane_x * sin(speed) + game->player.plane_y * cos(speed);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	speed = 0.075;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-speed) - game->player.dir_y * sin(-speed);
	game->player.dir_y = old_dir_x * sin(-speed) + game->player.dir_y * cos(-speed);

	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-speed) - game->player.plane_y * sin(-speed);
	game->player.plane_y = old_plane_x * sin(-speed) + game->player.plane_y * cos(-speed);
}
