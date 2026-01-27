/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/27 16:54:04 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	find_end(char **file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i--;
	while (i >= 0 && is_empty_line(file[i]))
		i--;
	return (i);
}

static int	scan_backwards(char **file, int i, int *found_map)
{
	int	j;
	int	result;

	j = i;
	*found_map = 0;
	while (j >= 0)
	{
		result = is_map_line(file[j]);
		if (result == -1)
			return (-1);
		if (result == 1)
			*found_map = 1;
		else if (result == 0 && !is_empty_line(file[j]))
			break ;
		j--;
	}
	return (j);
}

static int	trim_start(char **file, int i, int j)
{
	j++;
	while (j <= i && is_empty_line(file[j]))
		j++;
	return (j);
}

int	find_map(char **file, int *i, int *j)
{
	int	found_map;

	*i = find_end(file);
	*j = scan_backwards(file, *i, &found_map);
	if (*j == -1)
		return (-1);
	*j = trim_start(file, *i, *j);
	if (!found_map || *j > *i)
		return (-1);
	return (0);
}
