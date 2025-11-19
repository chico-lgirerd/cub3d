/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:43:27 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/19 20:29:34 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static void	draw_empty_cases(t_data *data, int x, int y)
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

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	data->minimap.start_x = (int)data->player.pos_x - MINIMAP_ZOOM / 2;
	data->minimap.start_y = (int)data->player.pos_y - MINIMAP_ZOOM / 2;
	x = 0;
	while (x < MINIMAP_ZOOM)
	{
		y = 0;
		while (y < MINIMAP_ZOOM)
		{
			data->minimap.map_x = data->minimap.start_x + x;
			data->minimap.map_y = data->minimap.start_y + y;
			if (data->minimap.map_y >= data->map_start
				&& data->minimap.map_y <= data->map_end
				&& data->minimap.map_x >= 0 && data->minimap.map_x
				< (int)ft_strlen(data->map[data->minimap.map_y]))
				draw_cases(data, x, y);
			else
				draw_empty_cases(data, x, y);
			y++;
		}
		x++;
	}
	draw_player(data);
}