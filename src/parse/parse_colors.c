/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/01 18:00:00 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	parse_value(char *str, int *i)
{
	int	value;

	while (str[*i] && (ft_isspace(str[*i]) || str[*i] == ','))
		(*i)++;
	if (!ft_isdigit(str[*i]))
		ft_error("Invalid RGB format");
	value = ft_atoi(&str[*i]);
	if (value < 0 || value > 255)
		ft_error("RGB value must be between 0-255");
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
	rgb.g = parse_value(line, &i);
	rgb.b = parse_value(line, &i);
	return (rgb);
}

void	get_colours(t_game *game, char **map)
{
	int		i;
	int		type;
	int		count;
	char	*colours[2];

	colours[F] = "F";
	colours[C] = "C";
	i = 0;
	count = 0;
	while (map[i] && count < 2)
	{
		type = get_type(map[i], colours, 2);
		if (type == F && game->parser.rgb[F].b == -1)
		{
			game->parser.rgb[F] = parse_rgb(get_path(map[i]));
			count++;
		}
		else if (type == C && game->parser.rgb[C].b == -1)
		{
			game->parser.rgb[C] = parse_rgb(get_path(map[i]));
			count++;
		}
		else if (type != -1)
			ft_error("Duplicate colour definition");
		i++;
	}
}
