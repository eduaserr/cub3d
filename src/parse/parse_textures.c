/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/01 18:13:38 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
			if (game->parser.imgsidewall[type])
				ft_error("Duplicate texture definition");
			game->parser.imgsidewall[type] = get_path(map[i]);
			count++;
		}
		i++;
	}
}
