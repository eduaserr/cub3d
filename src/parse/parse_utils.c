/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/04 06:09:47 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*get_path(char *line)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (line[i] && ft_isspace(line[i]))
		i++;
	// Saltar identificador (NO, SO, WE, EA, F, C)
	while (line[i] && !ft_isspace(line[i]))
		i++;
	// Saltar espacios/tabs
	while (line[i] && ft_isspace(line[i]))
		i++;
	path = ft_get_word(line, i);
	if (!path)
		return (NULL);
	return (path);
}

int	get_type(char *line, char **sides, int len)
{
	int	i;
	int	j;

	i = 0;
	// Saltar espacios iniciales
	while (line[i] && ft_isspace(line[i]))
		i++;
	// Buscar coincidencia
	j = 0;
	while (j < len)
	{
		if (!ft_strncmp(&line[i], sides[j], ft_strlen(sides[j]))
			&& ft_isspace(line[i + ft_strlen(sides[j])]))
			return (j);
		j++;
	}
	return (-1);
}
