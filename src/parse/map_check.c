/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/27 17:37:35 by eduaserr         ###   ########.fr       */
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
	if (!map[y] || x < 0 || x >= (int)ft_strlen(map[y]))
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
