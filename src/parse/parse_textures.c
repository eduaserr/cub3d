/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/01 03:19:17 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*get_path(char *line)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	// Saltar identificador (NO, SO, WE, EA)
	while (line[i] && !ft_isspace(line[i]))
		i++;
	// Saltar espacios/tabs
	while (line[i] && ft_isspace(line[i]))
		i++;
	path = ft_get_word(line, i);
	if (!path)
		ft_error("Memory allocation error");
	return (path);
}

int	get_type(char *line, char **sides, int len)
{
	int	i;
	int	j;

	i = 0;
	// Saltar espacios iniciales
	while (line[i] && ft_isspace(line[i]))
		i++;
	// Buscar coincidencia con NO, SO, WE, EA
	j = 0;
	while (j < len)
	{
		if (!ft_strncmp(&line[i], sides[j], ft_strlen(sides[j]))
			&& ft_isspace(line[i + ft_strlen(sides[j])]))
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
	char	*sides[4];

	sides[NORTH] = "NO";
	sides[SOUTH] = "SO";
	sides[WEST] = "WE";
	sides[EAST] = "EA";
	i = 0;
	count = 0;
	while (map[i] && count < 4)
	{
		type = get_type(map[i], sides, 4);
		if (type != -1)
		{
			// Ya existe?
			if (game->parser.imgsidewall[type])
				ft_error("Duplicate texture definition");
			game->parser.imgsidewall[type] = get_path(map[i]);
			count++;
		}
		i++;
	}
}
