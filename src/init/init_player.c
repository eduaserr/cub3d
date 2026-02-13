/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:44:17 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/13 23:14:43 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	set_player_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir_x = 0.0;
		p->dir_y = -1.0;
	}
	else if (c == 'S')
	{
		p->dir_x = 0.0;
		p->dir_y = 1.0;
	}
	else if (c == 'E')
	{
		p->dir_x = 1.0;
		p->dir_y = 0.0;
	}
	else if (c == 'W')
	{
		p->dir_x = -1.0;
		p->dir_y = 0.0;
	}
}

static void	set_plane(t_player *p, char c)
{
	if (c == 'N')
	{
		p->plane_x = 0.66;
		p->plane_y = 0.0;
	}
	else if (c == 'S')
	{
		p->plane_x = -0.66;
		p->plane_y = 0.0;
	}
	else if (c == 'E')
	{
		p->plane_x = 0.0;
		p->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		p->plane_x = 0.0;
		p->plane_y = -0.66;
	}
}

int	init_player(t_game *game)
{
	char	c;
	int		y;
	int		x;

	y = (int)game->player.y;
	x = (int)game->player.x;
	// Guardamos posición jugador y modificamos su casilla
	c = game->map.map[y][x];
	if (is_player(c))
	{
		// Sumamos 0.5 para estar en el centro entre x y x+1, no rompemos raycasting
		game->player.x = x + 0.5;
		game->player.y = y + 0.5;
		set_player_dir(&game->player, c);
		set_plane(&game->player, c);
		game->player.speed = 0.06;
		game->map.map[y][x] = '0'; // No hay pared para raycasting
		return (1);
	}
	return (0);
}
