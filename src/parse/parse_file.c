/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:55 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/27 22:40:40 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* int	valid_path(t_game *game, char **map, int y, int x, char search)
{
	if (!map ||  y < 0 || y >= game->map.length
		|| x < 0 || x >= game->width || !map[y])
		return (0);
	if (map[y][x] == game->wall)
		return (0);
	if (map[y][x] == search)
		return (1);
	if (valid_path(game, map, y + 1, x, search)
		|| valid_path(game, map, y - 1, x, search)
		|| valid_path(game, map, y, x - 1, search)
		|| valid_path(game, map, y, x + 1, search))
		return (1);
	return (0);
} */

static void	check_map(t_game *game, char **map)
{
	// por cada caracter 0, ver sus 4 lados y si hay un espacio en uno de ellos, error de mapa abierto.
	if (check_borders(map, game->map.length))
		return (ft_freematrix(&game->map.map)); // libero mapa para comprobar si fallo
	//valid_path(game, map, y, x, z);
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
