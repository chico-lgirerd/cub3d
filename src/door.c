/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:14:35 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/12 15:23:12 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_door(t_data *data)
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
			data->minimap.width, data->minimap.height);
	data->minimap_img.addr = mlx_get_data_addr(data->minimap_img.img_ptr,
			&data->minimap_img.bits_per_pixel,
			&data->minimap_img.size_line,
			&data->minimap_img.endian);
	data->minimap_img.width = data->minimap.width;
	data->minimap_img.height = data->minimap.height;
}
