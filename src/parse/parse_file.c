/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:55 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/09 05:33:15 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	valid_color(t_color color)
{
	return (color.r != -1 && color.g != -1 && color.b != -1);
}

static int	validate_colors(t_game *game)
{
	if (!valid_color(game->parser.rgb[F])
		|| !valid_color(game->parser.rgb[C]))
		return (0);
	return (1);
}

static int	check_map(t_game *game, char **map)
{
	// por cada caracter 0, ver sus 4 lados y si hay un espacio en uno de ellos, error de mapa abierto.
	if (check_borders(map, game->map.length))
		return (ft_freematrix(&game->map.map), 0); // libero mapa para comprobar si fallo
	return (1);
}

void	parse_file(t_game *game, char **file)
{
	get_sidetxt(game, file);
	// Validar que todas las texturas existen
	if (!game->parser.imgsidewall[NORTH] || !game->parser.imgsidewall[EAST]
		|| !game->parser.imgsidewall[SOUTH] || !game->parser.imgsidewall[WEST])
		return (free_all(game), ft_error("Missing texture(s)"));
	get_colors(game, file);
	if (!validate_colors(game)) // Validar que todos los colores fueron parseados
		return (free_all(game), ft_error("Missing colors(s)"));
	get_map(game, file);
	if (!game->map.map)
		return (free_all(game), ft_error("Invalid map")); //liberar en caso de error
	if (!check_map(game, game->map.map))
		return (free_all(game), ft_error("Map not closed"));
}