/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2025/12/21 03:57:09 by eduaserr         ###   ########.fr       */
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
	game->map.map = NULL;
	game->map.map = read_map(file_map);
	init_values(game);
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
	return 0;
}
