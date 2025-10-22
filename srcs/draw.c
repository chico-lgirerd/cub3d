/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:55:57 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/22 19:44:38 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../minilibx-linux/mlx.h"
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

void	draw_textured_wall(t_exec_data *data, int x, int start, int end)
{
	int				y;
	int				color;
	double			step;
	double			tex_pos;
	t_raycasting	rc;
	t_draw			*draw;

	rc = data->raycasting;
	draw = &data->raycasting.draw;
	if (rc.side == 0 && rc.raydir_x < 0)
		draw->tex = data->textures.east.img;
	else if (rc.side == 0 && rc.raydir_x > 0)
		draw->tex = data->textures.west.img;
	else if (rc.side == 1 && rc.raydir_y < 0)
		draw->tex = data->textures.north.img;
	else
		draw->tex = data->textures.south.img;
	draw->tex_x *= TEXTURE_WIDTH;
	if ((rc.side == 0 && rc.raydir_x < 0) || (rc.side == 1 && rc.raydir_y < 0))
		draw->tex_x = TEXTURE_WIDTH - draw->tex_x - 1;
	step = 1.0 * TEXTURE_HEIGHT / draw->line_height;
	tex_pos = (start - data->win_height / 2 + draw->line_height / 2) * step;
	y = start;
	while (y < end)
	{
		draw->tex_y = (int)tex_pos % TEXTURE_HEIGHT;
		tex_pos += step;
		color = get_texture_color();
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
	t_player		player;
	t_raycasting	rc;
	t_draw			*draw;

	player = data->player;
	rc = data->raycasting;
	draw = &data->raycasting.draw;
	if (rc.side == 0)
		wall_x = player.pos_y + rc.perp_walldist * rc.raydir_y;
	else
		wall_x = player.pos_x + rc.perp_walldist * rc.raydir_x;
	wall_x -= floor(wall_x);
	draw->tex_x = wall_x;
	draw->line_height = (int)data->win_height / rc.perp_walldist;
	draw->draw_start = -draw->line_height / 2 + data->win_height / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + data->win_height / 2;
	if (draw->draw_end > data->win_height)
		draw->draw_end = data->win_height - 1;
	draw_ceiling_floor(data, x, draw->draw_start, draw->draw_end);
	draw_textured_wall(data, x, draw->draw_start, draw->draw_end);
	(void)x;
}
