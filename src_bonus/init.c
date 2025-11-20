/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:04:43 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/20 11:54:05 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
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

int	init_map(t_data *data, char *filename)
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
	if (!have_textures(data->textures))
		return (1);
	if (handle_map_error(is_valid_map(data, data->map, data->map_start)))
		return (1);
	return (0);
}

void	init_player(t_player *player)
{
	player->pos_x = player->start_x + 0.5;
	player->pos_y = player->start_y + 0.5;
	if (player->start_char == 'N' || player->start_char == 'S')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		if (player->start_char == 'S')
			player->dir_y = 1;
		player->plane_x = 0.66;
		if (player->start_char == 'S')
			player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
	{
		player->dir_x = -1;
		if (player->start_char == 'E')
			player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
		if (player->start_char == 'E')
			player->plane_y = 0.66;
	}
}

void	init_image(t_data *data)
{
	data->buffer.width = data->win_width;
	data->buffer.height = data->win_height;
	data->buffer.img_ptr = mlx_new_image(data->mlx_ptr,
			data->buffer.width, data->buffer.height);
	if (!data->buffer.img_ptr)
	{
		printf("Error\nCould not create game image\n");
		secure_free(data);
	}
	data->buffer.addr = mlx_get_data_addr(data->buffer.img_ptr,
			&data->buffer.bits_per_pixel,
			&data->buffer.size_line,
			&data->buffer.endian);
	data->pause.width = data->win_width;
	data->pause.height = data->win_height;
	data->pause.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/pause.xpm",
			&data->pause.width, &data->pause.height);
	if (!data->pause.img_ptr)
	{
		printf("Error\nCould not load pause image\n");
		secure_free(data);
	}
}
