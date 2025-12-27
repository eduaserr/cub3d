/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/28 00:36:49 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_map(t_game *game, char **map)
{
	get_textures(game, map);
	if (!game->parser.imgsidewall[NORTH] || !game->parser.imgsidewall[EAST]
		|| !game->parser.imgsidewall[SOUTH] || !game->parser.imgsidewall[WEST])
		ft_error("Missing texture(s)");
}
