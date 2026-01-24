/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/24 22:22:58 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' 
		|| c == 'E' || c == 'W' || ft_isspace(c));
}

static int	valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' 
		|| c == 'E' || c == 'W' || c == ' ');
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
		{
			if (has_wall)
				return (ft_error2("Invalid character in map"), -1);
			return (0);
		}
		i++;
	}
	return (has_wall);
}

static int	validate_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!valid_map_char(line[i]))
			return (ft_error2("Invalid character in map"), 0);
		i++;
	}
	return (1);
}

static int	find_map(char **file, int *i, int *j)
{
	int	result;

	while (file[*i])
		(*i)++;
	(*i)--;
	*j = *i;
	while (*j >= 0)
	{
		result = is_map_line(file[*j]);
		if (result == -1)
			return (-1);
		if (!result)
			break ;
		(*j)--;
	}
	return (0);
}

void	get_map(t_game *game, char **file)
{
	int	i;
	int	j;
	int	start;

	// Encontrar última línea
	i = 0;
	if (find_map(file, &i, &j) == -1)
		return ;
	if (j >= i || j < 0)
		return ;
	start = j + 1;
	// Copiar desde start hasta i
	game->map.length = i - start + 1;
	game->map.map = ft_calloc(game->map.length + 1, sizeof(char *));
	if (!game->map.map)
		return (ft_error2("calloc allocation error"));
	j = 0;
	while (start <= i)
	{
		if (!validate_line(file[start]))
		{
			ft_freematrix(&game->map.map);
			return (ft_error2("Invalid character in map"));
		}
		game->map.map[j++] = ft_strdup(file[start++]);
	}
	game->map.map[j] = NULL;
}
