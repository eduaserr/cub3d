/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/27 23:28:55 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	find_player(t_game *game)
{
	int	y;
	int	x;
	int	count;

	y = -1;
	count = 0;
	while (++y < game->map.length)
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (is_player(game->map.map[y][x]))
			{
				game->player.x = x;
				game->player.y = y;
				count++;
				if (count > 1)
					return (ft_error2("Multiple players in map"), 0);
			}
			x++;
		}
	}
	if (count == 0)
		return (ft_error2("Player not found in map"), 0);
	return (1);
}

void	get_map(t_game *game, char **file)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	if (find_map(file, &i, &j) == -1)
		return ;
	start = j;
	game->map.length = i - start + 1;
	game->map.map = ft_calloc(game->map.length + 1, sizeof(char *));
	if (!game->map.map)
		return (ft_error2("calloc allocation error"));
	j = 0;
	while (start <= i)
		game->map.map[j++] = ft_strdup(file[start++]);
	game->map.map[j] = NULL;
	if (!find_player(game))
		ft_freematrix(&game->map.map);
}
