/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/04 07:22:53 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' 
		|| c == 'E' || c == 'W' || ft_isspace(c));
}

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	is_map_line(char *line)
{
	int	i;
	int	has_wall;

	if (is_empty_line(line))
		return (0);
	i = 0;
	has_wall = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			has_wall = 1;
		else if (!is_map_char(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	return (has_wall);
}

void	get_map(t_game *game, char **file)
{
	int	i;
	int	j;
	int	start;

	// Encontrar última línea
	i = 0;
	while (file[i])
		i++;
	i--;
	// Saltar líneas vacías del final
	while (i >= 0 && is_empty_line(file[i]))
		i--;
	// Retroceder mientras sea mapa válido
	j = i;
	while (j >= 0)
	{
		if (!is_map_line(file[j]))
			break;
		j--;
	}
	start = j + 1;
	// Copiar desde start hasta i
	game->map.length = i - start + 1;
	game->map.map = ft_calloc(game->map.length + 1, sizeof(char *));
	if (!game->map.map)
		return (ft_error2("calloc allocation error"));
	j = 0;
	while (start <= i)
		game->map.map[j++] = ft_strdup(file[start++]);
	game->map.map[j] = NULL;
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
		return (free_all(game), ft_error("Missing texture(s)"));
	get_map(game, file);
	if (!game->map.map)
		return (free_all(game), ft_error("Missing map"));
	//check_borders();
	//check_entities();
	//valid_path();
}
