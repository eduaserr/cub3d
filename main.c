/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paularuizalcarazgmail.com <paularuizalc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/29 20:14:47 by paularuizal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void	ft_error(char *str)
{
	ft_printf("\x1b[31m%s\x1B[37m%s\n", "Error : ", str);
	exit(EXIT_FAILURE);
}

int	check_extension(char *av)
{
	int	len;

	len = ft_strlen(av);
	while (av[len - 1] && ft_isspace(av[len - 1]))
		len--;
	if (len == 4)
		return (1);
	else if (ft_strncmp(&av[len - 4], ".cub", 4) == 0)
		return (0);
	return (1);
}

void	get_map(t_game *game, char *file_map)
{
	init_values(game);
	game->map.map = NULL;
	game->map.map = read_map(file_map);
	parse_map(game, game->map.map);
	game->map.cpymap = ft_arrdup(game->map.map);
	if (!game->map.cpymap)
	{
		free(game->map.map);
		//ft_freegame(game);
		ft_error("Unexpected arrdup error");
	}
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || check_extension(av[1]))
		ft_error("invalid arguments, map name/extension");
	get_map(&game, av[1]);
	ft_printf("sale de getmap\n");
	ft_printmatrix(game.map.map);
	init_player(&game);
	printf("Posición jugador: x=%f, y=%f\n", game.player.x, game.player.y);
	printf("Dirección jugador: dir_x=%f, dir_y=%f\n", game.player.dir_x, game.player.dir_y);
	int i = 0;
	while (i < 4)
		ft_printlines(game.parser.imgsidewall[i++]);
	return 0;
}
