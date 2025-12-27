/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/28 00:36:50 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

static char	**check_superline(char *superline)
{
	char	**map;

	if (!superline || !superline[0] || superline[0] == '\n')
		return (free(superline), ft_error("Empty map or line error"), NULL);
	map = ft_split(superline, '\n');
	if (!map)
		return (free(superline), ft_error("Split map error"), NULL);
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
	map = check_superline(superline);
	free(superline);
	superline = NULL;
	return (map);
}
