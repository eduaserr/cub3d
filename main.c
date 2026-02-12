/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr < eduaserr@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 03:22:02 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/10 18:19:18 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int	check_extension(char *av, char *str)
{
	int	len;

	len = ft_strlen(av);
	while (av[len - 1] && ft_isspace(av[len - 1]))
		len--;
	if (len == 4)
		return (1);
	else if (ft_strncmp(&av[len - 4], str, 4) == 0)
		return (0);
	return (1);
}

void	get_file(t_game *game, char *file_map)
{
	init_values(game);
	game->map.file = read_map(file_map);
	parse_file(game, game->map.file);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || check_extension(av[1], ".cub"))
		ft_error("invalid arguments, map name/extension");
	get_file(&game, av[1]);
	init_player(&game);
	init_mlx(&game);
	init_textures(&game);
	mlx_loop(game.mlx);
	free_all(&game);
	return (0);
}

/*
TODO
# 1. Mapa sin jugador
# 2. Múltiples jugadores
# 3. Texturas faltantes
# 4. Colores inválidos
# 5. Mapa no cerrado
# 6. Caracteres inválidos
# 7. Líneas vacías dentro del mapa

PARSER
comprobar que el path de la textura está completo. (solved, creo. need probar mas casos)
leak en parsergb si le pasas un rgb incompleto (solved)
seguir con comprobacion demapa.
bordes, entidades... (check)

Debo de mantener las lienas vacias dentro del mapa (culpa de gnl -> split) se salta las lineas vacias "" (solved)

En el chequeo guardar valores necesarios para facilitar la ejecucion
si hay 0, comprueba las paredes alrededor.


   1     1111111111111111111111111		(mapa valido)
        1000000000110000000000001
        1111111111111111111111111
  
¿Que sucede si hay una pared suelta fuera del mapa?
valido

SIEMPRE comprobar mallocs y memoria sin liberar.
Liberar en todas las salidas de error.

ft_error(char *str) muestra el mensaje(str) deseado y hace exit() dentro de la funcion,
por lo que se debe liberar todo lo necesario justo antes de llamar a esta funcion.
NO EDITAR ft_error().
ft_error2() simplemente muestra un mensaje de error pero no sale del programa

cambiar disposicion de los mensajes de errores, debe ser Error\n.

Liberar al final de la ejecucion. Gestión de ventanas y mlx.
*/