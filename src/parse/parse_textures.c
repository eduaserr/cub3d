/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/12 14:37:04 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	parse_path(char *path)
{
	int	fd;

	fd = 0;
	if (check_extension(path, ".png"))
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error2("File does not exist"), 1);
	close(fd);
	return (0);
}

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
	i = -1;
	count = 0;
	while (file[++i] && count < 4)
	{
		type = get_type(file[i], sides, 4);
		if (type != -1)
		{
			if (game->parser.imgsidewall[type])
				return (ft_error2("Duplicate texture definition"));
			game->parser.imgsidewall[type] = get_path(file[i]);
			if (!game->parser.imgsidewall[type])
				return (ft_error2("Memory allocation imgsidewall"));
			if (parse_path(game->parser.imgsidewall[type]))
				return (free_parser(game), ft_error2("Side image path"));
			count++;
		}
	}
}
