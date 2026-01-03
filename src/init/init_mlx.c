#include "../../inc/cub3d.h"

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		ft_error("MLX init failed");
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		ft_error("Image MLX creation failed");
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
