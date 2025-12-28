/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/28 19:07:59 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*get_texture_path(char *line)
{
	int		i;
	int		start;
	int		end;
	char	*path;

	i = 0;
	// Saltar identificador (NO, SO, WE, EA)
	while (line[i] && !ft_isspace(line[i]))
		i++;
	// Saltar espacios/tabs
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	// Encontrar final del path
	while (line[i] && line[i] != '\n' && line[i] != ' ' && line[i] != '\t')
		i++;
	end = i;
	// Extraer path
	path = ft_substr(line, start, end - start);
	if (!path)
		ft_error("Memory allocation error");
	return (path);
}

static int	get_texture_type(char *line, char **identifiers)
{
	int	i;
	int	j;

	i = 0;
	// Saltar espacios iniciales
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	// Buscar coincidencia con NO, SO, WE, EA
	j = 0;
	while (j < 4)
	{
		if (!ft_strncmp(&line[i], identifiers[j], 2)
			&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
			return (j);
		j++;
	}
	return (-1);
}

void	get_sidetxt(t_game *game, char **map)
{
	int		i;
	int		type;
	int		count;
	char	*identifiers[4];

	identifiers[NORTH] = "NO";
	identifiers[SOUTH] = "SO";
	identifiers[WEST] = "WE";
	identifiers[EAST] = "EA";
	i = 0;
	count = 0;
	while (map[i] && count < 4)
	{
		type = get_texture_type(map[i], identifiers);
		if (type != -1)
		{
			// Ya existe?
			if (game->parser.imgsidewall[type])
				ft_error("Duplicate texture definition");
			game->parser.imgsidewall[type] = get_texture_path(map[i]);
			count++;
		}
		i++;
	}
}
