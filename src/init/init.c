/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:12 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/28 00:14:52 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


char	*get_sideimg(char *line)
{
	int		i;
	int		start;
	int		end;
	char	*path;
	
	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	// Encontrar final del path
	while (line[i] && line[i] != '\n' && line[i] != ' ' && line[i] != '\t')
		i++;
	end = i;
	// Extraer path
	path = ft_substr(line, start, end - start);
	if (!path)
		ft_error("Memory allocation error");
	return (path);
}

static int	get_texture_type(char *line, char **identifiers)
{
	int	i;
	int	j;

	i = 0;
	// Saltar espacios iniciales
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	// Buscar coincidencia con NO, SO, WE, EA
	j = 0;
	while (j < 4)
	{
		if (!ft_strncmp(&line[i], identifiers[j], 2)
			&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
			return (j); // Retorna NORTH(0), SOUTH(1), EAST(2), WEST(3),
		j++;
	}
	return (-1);
}

void	get_files(t_game *game, char **map) // pasar copia del mapa¿?
{
	int		i;
	int		type;
	int		count;
	char	*cmp[4];

	cmp[0] = "NO";
	cmp[1] = "SO";
	cmp[2] = "EA";
	cmp[3] = "WE";
	i = 0;
	count = 0;
	type = 0;
	while (map[i] && count < 4)  // Hasta encontrar las 4 texturas
	{
		ft_printf("count = %d\n", count);
		type = get_texture_type(map[i], cmp);
		if (type != -1) // Si es una línea de textura válida
		{
			if (game->parser.imgsidewall[type])  // Ya existe?
				ft_error("Duplicate texture definition");
			game->parser.imgsidewall[type] = get_sideimg(map[i]);
			count++;
		}
		i++;
	}
}

void	parse_map(t_game *game, char **map)
{
	get_files(game, map);
	// Validar que todas las texturas existen
	if (!game->parser.imgsidewall[NORTH] || !game->parser.imgsidewall[EAST]
		|| !game->parser.imgsidewall[SOUTH] || !game->parser.imgsidewall[WEST])
		ft_error("Missing texture(s)");
	//check_borders();
	//check_entities();
	//valid_path();
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
	
	game->parser.imgsidewall[NORTH] = NULL;
	game->parser.imgsidewall[SOUTH] = NULL;
	game->parser.imgsidewall[WEST] = NULL;
	game->parser.imgsidewall[EAST] = NULL;
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

static char	**check_superline(char *superline)
{
	char	**map;

	if (!superline || !superline[0] || superline[0] == '\n')		// comprueba inicio del mapa
		return (free(superline), ft_error("Empty map or line error"), NULL);
	map = ft_split(superline, '\n');
	if (!map)
		return (free(superline), ft_error("Split map error"), NULL);
	//check surrounded by walls
	
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
