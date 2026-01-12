/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:51:32 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/12 14:41:26 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_error2(char *str)
{
	ft_printf("\x1b[31m%s\x1B[37m%s\n", "Error : ", str);
}

void	ft_error(char *str)
{
	ft_printf("\x1b[31m%s\x1B[37m%s\n", "Error : ", str);
	exit(EXIT_FAILURE);
}

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

void	print_all(t_game *game)
{
	int	i;

	//ft_printmatrix(game->map.file);
	//ft_printmatrix(game->map.cpyfile);
	ft_printf("\nPRINT MAP MATRIX\n");
	ft_printmatrix(game->map.map);
	ft_printf("\nPRINT PARSER STRUCT\n");
	i = 0;
	while (i < 4)
		ft_printlines(game->parser.imgsidewall[i++]);
	ft_printrgb(game);
}
