/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:06:00 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/22 19:11:05 by lgirerd          ###   ########lyon.fr   */
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

void	draw_cases(t_exec_data *data, int x, int y)
{
	int	case_w;
	int	case_h;
	int	px;
	int	py;
	int	color;

	case_w = data->minimap_width / data->map_width;
	case_h = data->minimap_height / data->map_height;
	if (data->map[y][x] > 0)
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

void	draw_player(t_exec_data *data, int player_x, int player_y)
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
