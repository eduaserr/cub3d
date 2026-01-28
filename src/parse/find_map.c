/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/27 17:23:49 by eduaserr         ###   ########.fr       */
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

static int	find_start(char **file, int i, int *found_map)
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

static int	skip_emptylines(char **file, int start, int end)
{
	end++;
	while (end <= start && is_empty_line(file[end]))
		end++;
	return (end);
}

int	find_map(char **file, int *i, int *j)
{
	int	found_map;

	*i = find_end(file);
	*j = find_start(file, *i, &found_map);
	if (*j == -1)
		return (-1);
	*j = skip_emptylines(file, *i, *j);
	if (!found_map || *j > *i)
		return (-1);
	return (0);
}
