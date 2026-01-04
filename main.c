/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/04 07:56:39 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void	ft_printrgb(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2){
		ft_printf("r %d\n", game->parser.rgb[i].r);
		ft_printf("g %d\n", game->parser.rgb[i].g);
		ft_printf("b %d\n", game->parser.rgb[i].b);
		i++;
	}
}

void	ft_error2(char *str)
{
	ft_printf("\x1b[31m%s\x1B[37m%s\n", "Error : ", str);
	exit(EXIT_FAILURE);
}

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

void	get_file(t_game *game, char *file_map)
{
	init_values(game);
	game->map.file = NULL;
	game->map.file = read_map(file_map);
	parse_file(game, game->map.file);
	game->map.cpyfile = ft_arrdup(game->map.file);
	if (!game->map.cpyfile)
	{
		free_all(game);
		ft_error("Unexpected arrdup error");
	}
}

void	free_all(t_game *game)
{
	int	i;

	if (game->map.file)
		ft_freematrix(&game->map.file);
	if (game->map.cpyfile)
		ft_freematrix(&game->map.cpyfile);
	if (game->map.map)
		ft_freematrix(&game->map.map);
	i = -1;
	while (++i < 4)
	{
		if (game->parser.imgsidewall[i])
		{
			free(game->parser.imgsidewall[i]);
			game->parser.imgsidewall[i] = NULL;
		}
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	game->map.file = NULL;
	game->map.cpyfile = NULL;
	game->map.map = NULL;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || check_extension(av[1]))
		ft_error("invalid arguments, map name/extension");
	get_file(&game, av[1]);
	ft_printmatrix(game.map.file);
	init_player(&game);
	printf("Posición jugador: x=%f, y=%f\n", game.player.x, game.player.y);
	printf("Dirección jugador: dir_x=%f, dir_y=%f\n", game.player.dir_x, game.player.dir_y);
	int i = 0;
	while (i < 4)
		ft_printlines(game.parser.imgsidewall[i++]);
	ft_printrgb(&game);
	init_mlx(&game);
	draw_map(&game);
	mlx_loop(game.mlx);
	ft_printmatrix(game.map.map);
	free_all(&game);
	return 0;
}



/*
TODO

PARSER
chequear que haya mapa. (SEGFAULT si no hay mapa en el file)
chequear que haya rgb. SEGFAULT igual que con el mapa.
con los paths no pasa

despues seguir con comprobacion demapa. 
bordes, entidades...

En el chequeo guardar valores necesarios para la ejecucion


SIEMPRE comprobar mallocs y memoria sin liberar.
Liberar en todas las salidas de error.
Liberar al final de la ejecucion.
*/