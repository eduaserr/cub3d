/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/12 01:56:24 by eduaserr         ###   ########.fr       */
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
		if (!ft_isspace(line[i]))
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
		else if (!is_map_char(line[i]))
			return (0);
		i++;
	}
	return (has_wall);
}

static void	find_map(char **file, int *i, int *j)
{
	while (file[*i])
		(*i)++;
	(*i)--;
	// Saltar líneas vacías del final
	while (*i >= 0 && is_empty_line(file[*i]))
		(*i)--;
	// Retroceder mientras sea mapa válido
	*j = *i;
	while (*j >= 0)
	{
		if (!is_map_line(file[*j]))
			break ;
		(*j)--;
	}
}

void	get_map(t_game *game, char **file)
{
	int	i;
	int	j;
	int	start;

	// Encontrar última línea
	i = 0;
	find_map(file, &i, &j);
	if (j == i)
		return ;
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
