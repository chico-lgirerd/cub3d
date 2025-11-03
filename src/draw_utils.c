/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:06:00 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/03 15:27:59 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <stdlib.h>

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	get_texture_color(t_wall *texture, int tex_x, int tex_y)
{
	int				bytes_per_pixel;
	int				offset;
	unsigned char	*pixel;
	int				color;

	bytes_per_pixel = texture->bpp / 8;		
	offset = tex_y * texture->length + tex_x * bytes_per_pixel;
	pixel = (unsigned char *)texture->addr + offset;
	color = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16) | (pixel[3] << 24);
	return (color);
}

void	draw_empty_cases(t_data *data, int x, int y)
{
	int	case_w;
	int	case_h;
	int	px;
	int	py;
	int	color;

	case_w = data->minimap_width / CASE_WIDTH;
	case_h = data->minimap_height / CASE_HEIGHT;
	color = rgb_to_int(0, 0, 100);
	px = 0;
	while (px < case_w)
	{
		py = 0;
		while (py < case_h)
		{
			my_mlx_pixel_put(&data->minimap_img,
				x * case_w + px, y * case_h + py, color);
			py++;
		}
		px++;
	}
}

void	draw_cases(t_data *data, int x, int y, int map_x, int map_y)
{
	int	case_w;
	int	case_h;
	int	px;
	int	py;
	int	color;

	case_w = data->minimap_width / CASE_WIDTH;
	case_h = data->minimap_height / CASE_HEIGHT;
	if (data->map[map_y][map_x] == '1')
		color = rgb_to_int(128, 128, 128);
	else
		color = rgb_to_int(30, 30, 30);
	px = 0;
	while (px < case_w)
	{
		py = 0;
		while (py < case_h)
		{
			my_mlx_pixel_put(&data->minimap_img,
				x * case_w + px, y * case_h + py, color);
			py++;
		}
		px++;
	}
}

void	draw_player(t_data *data, int player_x, int player_y)
{
	int	px;
	int	py;
	int	color;

	color = rgb_to_int(255, 0, 0);
	px = -2;
	while (px <= 2)
	{
		py = -2;
		while (py <= 2)
		{
			my_mlx_pixel_put(&data->minimap_img,
				player_x + px, player_y + py, color);
			py++;
		}
		px++;
	}
}
