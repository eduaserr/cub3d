/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr < eduaserr@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/26 20:41:32 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

static int	parse_filename(char *path)
{
	int	i;

	i = ft_istrrchr(path, '/');
	if (path[i + 1] == '.')
		return (1);
	return (0);
}

int	check_extension(char *av, char *str)
{
	int	len;

	len = ft_strlen(av);
	while (av[len - 1] && ft_isspace(av[len - 1]))
		len--;
	if (parse_filename(av))
		return (1);
	else if (ft_strncmp(&av[len - 4], str, 4) == 0)
		return (0);
	return (1);
}

static void	get_file(t_game *game, char *file_map)
{
	init_values(game);
	game->map.file = read_map(file_map);
	parse_file(game, game->map.file);
}

static void	exec(t_game *game)
{
	init_player(game);
	init_mlx(game);
	init_textures(game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || check_extension(av[1], ".cub"))
		ft_error("invalid arguments, map name/extension");
	get_file(&game, av[1]);
	exec(&game);
	free_all(&game);
	return (0);
}
