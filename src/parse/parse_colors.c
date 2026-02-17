/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr < eduaserr@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/17 20:43:07 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	parse_value(char *str, int *i)
{
	int	value;

	while (str[*i] && (ft_isspace(str[*i]) || str[*i] == ','))
		(*i)++;
	if (!ft_isdigit(str[*i]))
		return (ft_error2("Invalid RGB format"), -1);
	value = ft_atoi(&str[*i]);
	if (value < 0 || value > 255)
		return (ft_error2("RGB value must be between 0-255"), -1);
	while (str[*i] && ft_isdigit(str[*i]))
		(*i)++;
	return (value);
}

static t_color	parse_rgb(char *line)
{
	int		i;
	t_color	rgb;

	i = 0;
	rgb.r = parse_value(line, &i);
	if (rgb.r == -1)
		return (line = ft_free_str(&line), rgb);
	rgb.g = parse_value(line, &i);
	if (rgb.g == -1)
		return (line = ft_free_str(&line), rgb);
	rgb.b = parse_value(line, &i);
	if (rgb.b == -1)
		return (line = ft_free_str(&line), rgb);
	line = ft_free_str(&line);
	return (rgb);
}

static int	process_color(t_game *game, char *line, int type)
{
	if (game->parser.rgb[type].b != -1)
	{
		ft_error2("Duplicate colour definition");
		return (0);
	}
	game->parser.rgb[type] = parse_rgb(get_path(line));
	if (!valid_color(game->parser.rgb[type]))
		return (0);
	return (1);
}

void	get_colors(t_game *game, char **file)
{
	int		i;
	int		type;
	int		count;
	char	*colors[2];

	colors[F] = "F";
	colors[C] = "C";
	i = -1;
	count = 0;
	while (file[++i] && count < 2)
	{
		type = get_type(file[i], colors, 2);
		if (type == F || type == C)
		{
			if (!process_color(game, file[i], type))
				return ;
			count++;
		}
	}
}
