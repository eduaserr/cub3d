/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/27 17:36:25 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
