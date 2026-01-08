/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:00:00 by eduaserr          #+#    #+#             */
/*   Updated: 2026/01/06 16:11:56 by eduaserr         ###   ########.fr       */
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
	rgb.g = parse_value(line, &i);
	rgb.b = parse_value(line, &i);
	line = ft_free_str(&line);
	return (rgb);
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
		if (type == F && game->parser.rgb[F].b == -1)
		{
			game->parser.rgb[F] = parse_rgb(get_path(file[i]));
			count++;
		}
		else if (type == C && game->parser.rgb[C].b == -1)
		{
			game->parser.rgb[C] = parse_rgb(get_path(file[i]));
			count++;
		}
		else if (type != -1)
			return (ft_error2("Duplicate colour definition"));
	}
}
