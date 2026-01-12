/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:55 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/11 20:44:34 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_file(t_game *game, char **file)
{
	get_sidetxt(game, file);
	// Validar que todas las texturas existen
	if (!game->parser.imgsidewall[NORTH] || !game->parser.imgsidewall[EAST]
		|| !game->parser.imgsidewall[SOUTH] || !game->parser.imgsidewall[WEST])
		return (free_all(game), ft_error("Missing texture(s)"));
	get_colors(game, file);
	// Validar que todos los colores fueron parseados
	if (game->parser.rgb[F].b == -1 || game->parser.rgb[C].b == -1)
		return (free_all(game), ft_error("Missing colors(s)"));
	get_map(game, file);
	if (!game->map.map)
		return (free_all(game), ft_error("Missing map"));
	//check_borders();
	//check_entities();
	//valid_path();
}
