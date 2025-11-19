/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:55:57 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/19 16:14:45 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>

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

int	compute_tex_x(t_data *data)
{
	double		wall_x;
	int			tex_x;
	t_player	player;
	t_rays		rc;

	player = data->player;
	rc = data->rays;
	if (rc.side == 0)
		wall_x = player.pos_y + rc.perp_walldist * rc.raydir_y;
	else
		wall_x = player.pos_x + rc.perp_walldist * rc.raydir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * data->textures.width;
	if (!rc.door_seen && ((rc.side == 0 && rc.raydir_x > 0)
			|| (rc.side == 1 && rc.raydir_y > 0)))
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
	tex_pos = (draw->start - data->win_height / 2 + draw->line_height / 2)
		* step;
	y = draw->start;
	while (y < draw->end)
	{
		draw->tex_y = (int)tex_pos;
		if (draw->tex_y >= data->textures.height)
			draw->tex_y = data->textures.height - 1;
		tex_pos += step;
		color = get_texture_color(&draw->wall_tex, draw->tex_x, draw->tex_y);
		my_mlx_pixel_put(&data->buffer, x, y, color);
		y++;
	}
}

void	draw_ceiling_floor(t_data *data, int x, int start, int end)
{
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = color_to_int(data->textures.ceiling);
	floor_color = color_to_int(data->textures.floor);
	y = 0;
	while (y < start)
	{
		my_mlx_pixel_put(&data->buffer, x, y, ceiling_color);
		y++;
	}
	y = end;
	while (y < data->win_height)
	{
		my_mlx_pixel_put(&data->buffer, x, y, floor_color);
		y++;
	}
}

void	draw_map(t_data *data, int x)
{
	t_rays	*rc;
	t_draw	*draw;

	rc = &data->rays;
	draw = &data->rays.draw;
	draw->line_height = (int)data->win_height / rc->perp_walldist;
	draw->start = -draw->line_height / 2 + data->win_height / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_height / 2 + data->win_height / 2;
	if (draw->end > data->win_height)
		draw->end = data->win_height - 1;
	draw_ceiling_floor(data, x, draw->start, draw->end);
	if (rc->door_seen)
		draw->wall_tex = data->textures.door;
	else if (rc->side == 0 && rc->raydir_x < 0)
		draw->wall_tex = data->textures.east;
	else if (rc->side == 0 && rc->raydir_x > 0)
		draw->wall_tex = data->textures.west;
	else if (rc->side == 1 && rc->raydir_y < 0)
		draw->wall_tex = data->textures.north;
	else
		draw->wall_tex = data->textures.south;
	draw_textured_wall(data, x, draw);
	(void)x;
}
