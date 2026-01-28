#include "../../inc/cub3d.h"

void	exec_dda(t_game *game, t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	if (game->map.map[ray->map_y][ray->map_x] == '1')
		ray->hit = 1;
}

void	calc_wall_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x / 2) / ray->ray_dir_x);
	else
		ray->wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y / 2) / ray->ray_dir_y);
}

void	calc_line_height(t_ray *ray)
{
	ray->line_height = (int)WIN_HEIGHT / ray->wall_dist;
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end < 0)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int			y;
	uint32_t	color;

	if (ray->side == 0)
		color = 0xFF0000FF;
	else
		color = 0xAA0000FF;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}