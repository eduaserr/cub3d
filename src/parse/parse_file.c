/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:55 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/23 00:27:20 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_playable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_nonplayable(char c)
{
	return (ft_isspace(c));
}

char	get_tile(char **map, int y, int x)
{
	if (!map[y] || x < 0 || x >= ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}

int	check_tiles(char **map, int y, int x, int len)
{
	if (y == 0 || y == len - 1)
		return (ft_error2("Map not closed: edge"), 1);
	if (is_nonplayable(get_tile(map, y - 1, x)))
		return (ft_error2("Map not closed: top"), 1);
	if (is_nonplayable(get_tile(map, y + 1, x)))
		return (ft_error2("Map not closed: bottom"), 1);
	if (is_nonplayable(get_tile(map, y, x - 1)))
		return (ft_error2("Map not closed: left"), 1);
	if (is_nonplayable(get_tile(map, y, x + 1)))
		return (ft_error2("Map not closed: right"), 1);
	return (0);
}

int	check_borders(char **map, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (map[i][j])
		{
			if (is_playable(map[i][j]))
			{
				if (check_tiles(map, i, j, len))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

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
		return (free_all(game), ft_error("Missing map"));
	check_map(game, game->map.map);
	if (!game->map.map)
		return (free_all(game), ft_error("Check map"));
	//liberar en caso de error
}
