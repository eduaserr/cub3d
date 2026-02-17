/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 23:54:52 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/16 23:48:08 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0; // campo de visión
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x; //dirección del rayo
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->hit = 0;
}

void	calc_delta_dist(t_ray *ray)
{
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	calc_step_side(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		calc_delta_dist(&ray);
		calc_step_side(game, &ray);
		exec_dda(game, &ray);
		calc_wall_dist(game, &ray);
		calc_wall_x(game, &ray);
		calc_line_height(&ray);
		init_texture_vars(game, &ray);
		draw_vertical_line(game, &ray, x);
		x++;
	}
}
