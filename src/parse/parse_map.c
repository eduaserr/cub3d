/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/02 02:45:28 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_map(t_game *game, char **map)
{
	get_sidetxt(game, map);
	// Validar que todas las texturas existen
	if (!game->parser.imgsidewall[NORTH] || !game->parser.imgsidewall[EAST]
		|| !game->parser.imgsidewall[SOUTH] || !game->parser.imgsidewall[WEST])
		ft_error("Missing texture(s)");
	get_colors(game, map);
	// Validar que todos los colores fueron parseados
	if (game->parser.rgb[F].b == -1 || game->parser.rgb[C].b == -1)
		ft_error("Missing colours(s)");
	//get_map(game, map);
	//check_borders();
	//check_entities();
	//valid_path();
}
