/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/27 22:22:11 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' 
		|| c == 'E' || c == 'W' || c == ' ');
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
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
		else if (!valid_char(line[i]))
		{
			if (has_wall)
				return (ft_error2("Invalid character in map"), -1);
			return (0);
		}
		i++;
	}
	return (has_wall);
}
