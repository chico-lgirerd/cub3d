/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:06:00 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/04 16:40:31 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <stdlib.h>

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
	double	case_w;
	double	case_h;
	int		px;
	int		py;
	int		color;

	case_w = (double)data->minimap.width / MINIMAP_ZOOM;
	case_h = (double)data->minimap.height / MINIMAP_ZOOM;
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

void	draw_cases(t_data *data, int x, int y)
{
	double	case_w;
	double	case_h;
	int		px;
	int		py;
	int		color;

	case_w = (double)data->minimap.width / MINIMAP_ZOOM;
	case_h = (double)data->minimap.height / MINIMAP_ZOOM;
	if (data->map[data->minimap.map_y][data->minimap.map_x] == '1')
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

void	draw_player(t_data *data)
{
	int	px;
	int	py;
	int	player_x;
	int	player_y;
	int	color;

	player_x = data->minimap.width / 2;
	player_y = data->minimap.height / 2;
	color = rgb_to_int(255, 0, 0);
	px = -2;
	while (px <= 1)
	{
		py = -2;
		while (py <= 1)
		{
			my_mlx_pixel_put(&data->minimap_img,
				player_x + px, player_y + py, color);
			py++;
		}
		px++;
	}
}
