/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:55:57 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/23 20:03:43 by tiaperei         ###   ########.fr       */
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

void	draw_textured_wall(t_exec_data *data, int x, int start, int end)
{
	int				y;
	int				color;
	t_raycasting	rc;
	t_draw			*draw;

	rc = data->raycasting;
	draw = &data->raycasting.draw;
	if (rc.side == 0 && rc.raydir_x < 0)
		draw->wall_tex = data->textures.east;
	else if (rc.side == 0 && rc.raydir_x > 0)
		draw->wall_tex = data->textures.west;
	else if (rc.side == 1 && rc.raydir_y < 0)
		draw->wall_tex = data->textures.north;
	else
		draw->wall_tex = data->textures.south;
	draw->tex_x = draw->tex_x * data->textures.width;
	if ((rc.side == 0 && rc.raydir_x > 0) || (rc.side == 1 && rc.raydir_y > 0))
		draw->tex_x = data->textures.width - draw->tex_x - 1;
	draw->step = 1.0 * data->textures.height / draw->line_height;
	draw->tex_pos = (start - data->win_height / 2 + draw->line_height / 2)
			* draw->step;
	y = start;
	while (y < end)
	{
		draw->tex_y = (int)draw->tex_pos;
		if (draw->tex_y >= data->textures.height)
			draw->tex_y = data->textures.height - 1;
		draw->tex_pos += draw->step;
		color = get_texture_color(&draw->wall_tex, draw->tex_x, draw->tex_y);
		my_mlx_pixel_put(&data->game_img, x, y, color);
		y++;
	}	
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
	t_draw			*draw;

	player = &data->player;
	rc = &data->raycasting;
	draw = &data->raycasting.draw;
	if (rc->side == 0)
		wall_x = player->pos_y + rc->perp_walldist * rc->raydir_y;
	else
		wall_x = player->pos_x + rc->perp_walldist * rc->raydir_x;
	wall_x -= floor(wall_x);
	draw->tex_x = wall_x;
	draw->line_height = (int)data->win_height / rc->perp_walldist;
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
