#include "../../inc/cub3d.h"

void	calc_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.x + ray->wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}
