/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:12 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/01 03:52:48 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_values(t_game *game)
{
	int	i;

	game->map.map = NULL;
	game->map.cpymap = NULL;
	game->map.length = 0;
	game->map.width = 0;
	game->map.floor = 0;
	game->map.wall = 0;
	game->map.player = 0;
	i = -1;
    while (++i < 4)
        game->parser.imgsidewall[i] = NULL;
    i = -1;
    while (++i < 2)
    {
        game->parser.rgb[i].r = -1;
        game->parser.rgb[i].g = -1;
        game->parser.rgb[i].b = -1;
    }
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.dir_x = 0.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.0;
}
