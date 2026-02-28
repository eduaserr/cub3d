/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/28 20:57:19 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	validate_map(char **file, int config_end)
{
    int	i;
    int	result;

    i = config_end - 1;
    while (i >= 0)
    {
        result = is_map_line(file[i]);
        if (result == -1)
            return (ft_error2("Invalid character out of map"), -1);
        if (result == 1)
            return (ft_error2("Map islands detected"), -1);
        i--;
    }
    return (0);
}

static int	process_line(char **file, int j, int *map_ended, int *found_map)
{
    int	result;

    result = is_map_line(file[j]);
    if (result == -1)
        return (-1);
    if (result == 1)
    {
        if (*map_ended)
            return (ft_error2("Map has empty lines inside"), -1);
        *found_map = 1;
        return (0);
    }
    if (result == 0 && !is_empty_line(file[j]))
    {
        if (validate_map(file, j) == -1)
            return (-1);
        return (1);
    }
    if (is_empty_line(file[j]) && *found_map)
        *map_ended = 1;
    return (0);
}

static int	find_start(char **file, int end, int *found_map)
{
    int	j;
    int	map_ended;
    int	status;

    j = end;
    *found_map = 0;
    map_ended = 0;
    while (j >= 0)
    {
        status = process_line(file, j, &map_ended, found_map);
        if (status == -1)
            return (-1);
        if (status == 1)
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
        return (1);
    *j = skip_emptylines(file, *i, *j);
    if (!found_map || *j > *i)
        return (ft_error2("No valid map found"), 1);
    return (0);
}