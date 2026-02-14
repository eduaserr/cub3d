/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduaserr <eduaserr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:49:28 by eduaserr          #+#    #+#             */
/*   Updated: 2026/02/14 13:13:02 by eduaserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static uint32_t	blend_alpha(uint32_t fg, uint32_t bg)
{
	uint8_t	alpha;
	uint8_t	inv_alpha;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	alpha = fg & 0xFF;
	inv_alpha = 255 - alpha;
	r = ((((fg >> 24) & 0xFF) * alpha) + (((bg >> 24) & 0xFF) * inv_alpha)) / 255;
	g = ((((fg >> 16) & 0xFF) * alpha) + (((bg >> 16) & 0xFF) * inv_alpha)) / 255;
	b = ((((fg >> 8) & 0xFF) * alpha) + (((bg >> 8) & 0xFF) * inv_alpha)) / 255;
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

static uint32_t	get_pixel(mlx_image_t *img, int x, int y)
{
	uint8_t	*pixel;

	pixel = &img->pixels[(y * img->width + x) * 4];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

uint32_t	blend_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	uint32_t	bg_color;
	uint32_t	final_color;

	bg_color = get_pixel(img, x, y);
	final_color = blend_alpha(color, bg_color);
	return (final_color);
}
