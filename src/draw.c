/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:55:57 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/03 15:43:27 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <math.h>

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	player_x;
	int	player_y;
	int start_x;
	int start_y;

	start_x = (int)data->player.pos_x - CASE_WIDTH / 2;
	start_y = (int)data->player.pos_y - CASE_HEIGHT / 2;
	x = 0;
	//#include <stdio.h>
	//printf("%d\n", data->minimap_height);
	while (x < CASE_WIDTH)
	{
		y = 0;
		while (y < CASE_HEIGHT)
		{
			int map_x = start_x + x;
			int map_y = start_y + y;
			if (map_x >= 0 && map_x < data->map_width && map_y >= 0 && map_y < data->map_height)
				draw_cases(data, x, y, map_x, map_y);
			else
				draw_empty_cases(data, x, y);
			y++;
		}
		x++;
	}
	player_x = data->minimap_width / 2;
	player_y = data->minimap_width / 2;
	draw_player(data, player_x, player_y);
}

int	compute_tex_x(t_data *data)
{
	double			wall_x;
	int				tex_x;
	t_player		player;
	t_raycasting	rc;

	player = data->player;
	rc = data->raycasting;
	if (rc.side == 0)
		wall_x = player.pos_y + rc.perp_walldist * rc.raydir_y;
	else
		wall_x = player.pos_x + rc.perp_walldist * rc.raydir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * data->textures.width;
	if ((rc.side == 0 && rc.raydir_x > 0) || (rc.side == 1 && rc.raydir_y > 0))
		tex_x = data->textures.width - tex_x - 1;
	return (tex_x);
}

void	draw_textured_wall(t_data *data, int x, t_draw *draw)
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;
	
	draw->tex_x = compute_tex_x(data);
	step = 1.0 * data->textures.height / draw->line_height;
	tex_pos = (draw->start - data->win_height / 2 + draw->line_height / 2) * step;
	y = draw->start;
	while (y < draw->end)
	{
		draw->tex_y = (int)tex_pos;
		if (draw->tex_y >= data->textures.height)
			draw->tex_y = data->textures.height - 1;
		tex_pos += step;
		color = get_texture_color(&draw->wall_tex, draw->tex_x, draw->tex_y);
		my_mlx_pixel_put(&data->game_img, x, y, color);
		y++;
	}
}

void	draw_ceiling_floor(t_data *data, int x, int start, int end)
{
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = rgb_to_int(20, 50, 50);
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

void	draw_map(t_data *data, int x)
{
	t_raycasting	rc;
	t_draw			*draw;

	rc = data->raycasting;
	draw = &data->raycasting.draw;
	draw->line_height = (int)data->win_height / rc.perp_walldist;
	draw->start = -draw->line_height / 2 + data->win_height / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_height / 2 + data->win_height / 2;
	if (draw->end > data->win_height)
		draw->end = data->win_height - 1;
	draw_ceiling_floor(data, x, draw->start, draw->end);
	if (rc.side == 0 && rc.raydir_x < 0)
		draw->wall_tex = data->textures.east;
	else if (rc.side == 0 && rc.raydir_x > 0)
		draw->wall_tex = data->textures.west;
	else if (rc.side == 1 && rc.raydir_y < 0)
		draw->wall_tex = data->textures.north;
	else
		draw->wall_tex = data->textures.south;
	draw_textured_wall(data, x, draw);
	(void)x;
}
