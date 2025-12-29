/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:12 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/28 00:36:51 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_values(t_game *game)
{
	game->map.map = NULL;
	game->map.cpymap = NULL;
	game->map.length = 0;
	game->map.width = 0;
	game->map.floor = 0;
	game->map.wall = 0;
	game->map.player = 0;
	game->parser.imgsidewall[NORTH] = NULL;
	game->parser.imgsidewall[SOUTH] = NULL;
	game->parser.imgsidewall[WEST] = NULL;
	game->parser.imgsidewall[EAST] = NULL;
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.dir_x = 0.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.0;
}
