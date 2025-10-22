/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:55:57 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/22 19:10:52 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <math.h>

void	draw_minimap(t_exec_data *data)
{
	int	x;
	int	y;
	int	player_x;
	int	player_y;

	x = 0;
	while (x < data->map_width)
	{
		y = 0;
		while (y < data->map_height)
		{
			draw_cases(data, x, y);
			y++;
		}
		x++;
	}
	player_x = (int)(data->player.pos_x
			* (data->minimap_width / data->map_width));
	player_y = (int)(data->player.pos_y
			* (data->minimap_width / data->map_height));
	draw_player(data, player_x, player_y);
}

void	draw_simple_wall(t_exec_data *data, int x, int start, int end)
{
	int				y;
	int				color;
	t_raycasting	rc;

	rc = data->raycasting;
	if (data->map[rc.map_y][rc.map_x] > 0)
		color = rgb_to_int(128, 128, 128);
	else
		color = rgb_to_int(255, 255, 255);
	y = start;
	while (y < end)
	{
		my_mlx_pixel_put(&data->game_img, x, y, color);
		y++;
	}
}

void	draw_ceiling_floor(t_exec_data *data, int x, int start, int end)
{
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = rgb_to_int(100, 100, 255);
	floor_color = rgb_to_int(50, 50, 50);
	y = 0;
	while (y < start)
	{
		my_mlx_pixel_put(&data->game_img, x, y, ceiling_color);
		y++;
	}
	y = end;
	while (y < data->win_height)
	{
		my_mlx_pixel_put(&data->game_img, x, y, floor_color);
		y++;
	}
}

void	draw_map(t_exec_data *data, int x)
{
	double			wall_x;
	t_player		*player;
	t_raycasting	*rc;
	t_line			*line;

	player = &data->player;
	rc = &data->raycasting;
	line = &data->raycasting.line;
	if (rc->side == 0)
		wall_x = player->pos_y + rc->perp_walldist * rc->raydir_y;
	else
		wall_x = player->pos_x + rc->perp_walldist * rc->raydir_x;
	wall_x -= floor(wall_x);
	line->tex_x = wall_x;
	line->line_height = (int)data->win_height / rc->perp_walldist;
	line->draw_start = -line->line_height / 2 + data->win_height / 2;
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line->line_height / 2 + data->win_height / 2;
	if (line->draw_end > data->win_height)
		line->draw_end = data->win_height - 1;
	draw_ceiling_floor(data, x, line->draw_start, line->draw_end);
	draw_simple_wall(data, x, line->draw_start, line->draw_end);
	(void)x;
}
