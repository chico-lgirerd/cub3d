/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:04:43 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/22 19:08:39 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

void	init_colors(t_color *ceiling, t_color *floor)
{
	ceiling->red = -1;
	ceiling->green = -1;
	ceiling->blue = -1;
	floor->red = -1;
	floor->green = -1;
	floor->blue = -1;
}

int	init_map(t_exec_data *data, char *filename)
{
	int	line_idx;

	init_colors(&data->textures.ceiling, &data->textures.floor);
	data->map = map_from_file(filename);
	if (!data->map)
	{
		printf("Error\nCould not get map from file : %s\n", filename);
		return (1);
	}
	line_idx = 0;
	while (data->map[line_idx] && !is_map_line(data->map[line_idx]))
	{
		if (get_textures(data, data->map[line_idx]))
			return (1);
		line_idx++;
	}
	data->map_start = line_idx;
	if (handle_map_error(is_valid_map(data, data->map, data->map_start)))
		return (1);
	if (!have_textures(data->textures))
		return (1);
	return (0);
}

void	init_player(t_player *player)
{
	player->pos_x = 20;
	player->pos_y = 20;
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

void	init_image(t_exec_data *data)
{
	data->game_img.img_ptr = mlx_new_image(data->mlx_ptr,
			data->win_width, data->win_height);
	data->game_img.addr = mlx_get_data_addr(data->game_img.img_ptr,
			&data->game_img.bits_per_pixel,
			&data->game_img.size_line,
			&data->game_img.endian);
	data->game_img.width = data->win_width;
	data->game_img.height = data->win_height;	
	data->minimap_img.img_ptr = mlx_new_image(data->mlx_ptr,
			data->minimap_width, data->minimap_height);
	data->minimap_img.addr = mlx_get_data_addr(data->minimap_img.img_ptr,
			&data->minimap_img.bits_per_pixel,
			&data->minimap_img.size_line,
			&data->minimap_img.endian);
	data->minimap_img.width = data->minimap_width;
	data->minimap_img.height = data->minimap_height;
}
