/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr < eduaserr@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/10 18:18:48 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	count_lines(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	if (i > 0 && s[i - 1] != c)
		count++;
	return (count);
}

static char	*extract_line(char const *s, int *start, char c)
{
	int		end;
	char	*substr;

	end = *start;
	while (s[end] && s[end] != c)
		end++;
	substr = ft_substr(s, *start, end - *start);
	if (s[end] == c)
		*start = end + 1;
	else
		*start = end;
	return (substr);
}

//este split no se salta las lineas vacias (las guarda)
static char	**ft_split_lines(char const *s, char c)
{
	char	**str;
	int		i;
	int		start;

	i = 0;
	start = 0;
	str = ft_calloc(count_lines(s, c) + 1, sizeof(char *));
	if (!str || !s)
		return (NULL);
	while (s[start])
	{
		str[i] = extract_line(s, &start, c);
		if (!str[i])
			return (ft_freematrix(&str), NULL);
		i++;
	}
	str[i] = NULL;
	return (str);
}

static char	*get_line(int fd)
{
	char	*superline;
	char	*line;

	superline = NULL;
	line = get_next_line(fd);
	while (line)
	{
		superline = ft_strjoin_gnl(superline, line);
		line = ft_free_str(&line);
		line = get_next_line(fd);
	}
	superline = ft_strjoin_gnl(superline, line);
	line = ft_free_str(&line);
	return (superline);
}

char	**read_map(char *filemap)
{
	char	**map;
	char	*superline;
	int		fd;
	int		i;

	superline = NULL;
	fd = open(filemap, O_RDONLY);
	if (fd < 0)
		ft_error("Open fd error");
	superline = get_line(fd);
	close(fd);
	i = 0;
	while (ft_isspace(superline[i]))
		i++;
	if (!superline || !superline[0] || !superline[i])
		return (free(superline), ft_error("Empty map or line error"), NULL);
	map = ft_split_lines(superline, '\n');
	free(superline);
	if (!map)
		return (ft_error("Split map error"), NULL);
	return (map);
}
