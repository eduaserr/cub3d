/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:12 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/23 03:03:33 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	validate_map(char **map, int len)
{
	int	i;
	int	j;
	char	line;

	j = 0;
	i = 0;
	line = NULL;
	while (j < len)
	{
		while (map[j][i] == ' ' || map[j][i] == '\t')
			i++;
		if (!ft_strncmp(&map[j][i], "NO ", 3))
			line =  ft_substr();
		else if (!ft_strncmp(&map[j][i], "SO ", 3))
			line =  ft_substr();
		else if (!ft_strncmp(&map[j][i], "WE ", 3))
			line =  ft_substr();
		else if (!ft_strncmp(&map[j][i], "EA ", 3))
			line =  ft_substr();
		j++;
	}
}


void	init_values(t_game *game)
{
	game->map.map = NULL;
	game->map.cpymap = NULL;
	game->map.length = 0;
	game->map.width = 0;
	game->map.floor = 0;
	game->map.wall = 0;
	game->map.player = 0;
}

static char	*get_line(int fd, int *len)
{
	char	*superline;
	char	*line;

	superline = NULL;
	line = get_next_line(fd);
	while (line)
	{
		*len += 1;
		superline = ft_strjoin_gnl(superline, line);
		line = ft_free_str(&line);
		line = get_next_line(fd);
	}
	superline = ft_strjoin_gnl(superline, line);
	line = ft_free_str(&line);
	return (superline);
}

static char	**check_superline(char *superline, int len)
{
	char	**map;
	int		i;
	int		len_check;
	int		len_current;

	if (!superline || !superline[0] || superline[0] == '\n')		// comprueba inicio del mapa
		return (free(superline), ft_error("Empty map or line error"), NULL);
	map = ft_split(superline, '\n');
	if (!map)
		return (free(superline), ft_error("Split map error"), NULL);

	//comprobación de limites y parseo de mapa

	//validate_map(map, len);

	return (map);
}

char	**read_map(char *filemap)
{
	char	**map;
	char	*superline;
	int		fd;
	int		len;

	superline = NULL;
	len = 0;
	fd = open(filemap, O_RDONLY);
	if (fd < 0)
		ft_error("Open fd error");
	superline = get_line(fd, &len);
	close(fd);
	map = check_superline(superline, len);
	free(superline);
	superline = NULL;
	return (map);
}
