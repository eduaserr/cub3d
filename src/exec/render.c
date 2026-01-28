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
	draw_background(game);
//	mlx_delete_image(game->mlx, game->img);
//	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	raycasting(game);
//	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
