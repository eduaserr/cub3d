/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruiz-al <pruiz-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 23:55:31 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/26 20:25:25 by pruiz-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	calc_tex_x(t_game *game, t_ray *ray, int tex_id)
{
	int	tex_width;

	tex_width = game->tex[tex_id]->width;
	ray->tex_x = (int)(ray->wall_x * tex_width);
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		ray->tex_x = tex_width - ray->tex_x - 1;
}
