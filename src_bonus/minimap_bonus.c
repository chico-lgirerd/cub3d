/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:43:27 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/24 19:28:49 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	draw_empty_cases(t_data *data, int x, int y)
{
	double	case_w;
	double	case_h;
	int		px;
	int		py;
	int		color;

	case_w = (double)data->minimap.width / 15;
	case_h = (double)data->minimap.height / 15;
	color = rgb_to_int(30, 30, 30);
	px = 0;
	while (px < case_w)
	{
		py = 0;
		while (py < case_h)
		{
			my_mlx_pixel_put(&data->buffer,
				x * case_w + px + 10, y * case_h + py + 10, color);
			py++;
		}
		px++;
	}
}

static void	draw_cases(t_data *data, int x, int y)
{
	double	case_w;
	double	case_h;
	int		px;
	int		py;
	int		color;

	case_w = (double)data->minimap.width / 15;
	case_h = (double)data->minimap.height / 15;
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
			my_mlx_pixel_put(&data->buffer,
				x * case_w + px + 10, y * case_h + py + 10, color);
			py++;
		}
		px++;
	}
}

static void	draw_player(t_data *data)
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
			my_mlx_pixel_put(&data->buffer,
				player_x + px + 10, player_y + py + 10, color);
			py++;
		}
		px++;
	}
}

void	draw_minimap_border(t_data *data, int x, int y)
{
	int	i;
	int	color;
	int	offset;

	color = rgb_to_int(180, 150, 0);
	offset = 0;
	while (offset < 4)
	{
		i = -1;
		while (i++ < data->minimap.width)
		{
			my_mlx_pixel_put(&data->buffer, x + i, y + offset, color);
			my_mlx_pixel_put(&data->buffer,
				x + i, y + data->minimap.height - 1 - offset, color);
		}
		i = -1;
		while (i++ < data->minimap.height)
		{
			my_mlx_pixel_put(&data->buffer, x + offset, y + i, color);
			my_mlx_pixel_put(&data->buffer,
				x + data->minimap.width - 1 - offset, y + i, color);
		}
		offset++;
	}
}

void	draw_minimap(t_data *data)
{
	int			x;
	int			y;
	t_minimap	*minimap;

	minimap = &data->minimap;
	minimap->start_x = (int)data->player.pos_x - 15 / 2;
	minimap->start_y = (int)data->player.pos_y - 15 / 2;
	x = 0;
	while (x < 15)
	{
		y = 0;
		while (y < 15)
		{
			minimap->map_x = data->minimap.start_x + x;
			minimap->map_y = data->minimap.start_y + y;
			if (map_in_border(data, minimap->map_x, minimap->map_y))
				draw_cases(data, x, y);
			else
				draw_empty_cases(data, x, y);
			y++;
		}
		x++;
	}
	draw_player(data);
	draw_minimap_border(data, 10, 10);
}
