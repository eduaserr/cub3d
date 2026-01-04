/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/04 07:13:07 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	get_sidetxt(t_game *game, char **file)
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
	while (file[i] && count < 4)
	{
		type = get_type(file[i], sides, 4);
		if (type != -1)
		{
			// Ya existe?
			if (game->parser.imgsidewall[type])
				return (ft_error2("Duplicate texture definition\n"));
			game->parser.imgsidewall[type] = get_path(file[i]);
			if (!game->parser.imgsidewall[type])
				return (ft_error2("Memory allocation imgsidewall\n"));
			count++;
		}
		i++;
	}
}
