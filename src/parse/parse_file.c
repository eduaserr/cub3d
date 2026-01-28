/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:55 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/27 17:37:35 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_map(t_game *game, char **map)
{
	// por cada caracter 0, ver sus 4 lados y si hay un espacio en uno de ellos, error de mapa abierto.
	if (check_borders(map, game->map.length))
		return (ft_freematrix(&game->map.map)); // libero mapa para comprobar si fallo
	//valid_path();
}

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
		return (free_all(game), ft_error("Invalid map"));
	check_map(game, game->map.map);
	if (!game->map.map)
		return (free_all(game), ft_error("Check map"));
	//liberar en caso de error
}
