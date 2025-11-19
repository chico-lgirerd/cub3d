/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   totem.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:25:27 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/19 20:32:20 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <math.h>

void	init_totem(t_data *data)
{
	data->totem.width = 500;
	data->totem.height = 500;
	data->totem.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/totem.xpm",
			&data->totem.width, &data->totem.height);
	data->totem.addr = mlx_get_data_addr(data->totem.img_ptr,
			&data->totem.bits_per_pixel, &data->totem.size_line,
			&data->totem.endian);
}

void	draw_totem(t_data *data, int pos_x, int pos_y, int *image)
{
	int	x;
	int	y;
	int	*totem_data;
	int	color;

	totem_data = (int *)data->totem.addr;
	y = 0;
	while (y < data->totem.height)
	{
		x = 0;
		while (x < data->totem.width)
		{
			color = totem_data[y * (data->totem.size_line / 4) + x];
			if ((color & 0x00FFFFFF) != 0x000000)
			{
				if (pos_x + x >= 0 && pos_x + x < data->buffer.width
					&& pos_y + y >= 0 && pos_y + y < data->buffer.height)
					image[(pos_y + y) * (data->buffer.size_line / 4)
						+ (pos_x + x)] = color;
			}
			x++;
		}
		y++;
	}
}

void	animate_totem(t_data *data, int base_x, int base_y)
{
	static float	phase = 1.5f;
	int				offset_y;
	int				anim_pos_y;

	offset_y = (int)(sin(phase) * 12);
	anim_pos_y = base_y + offset_y;
	if (data->key.key_sprint)
		phase += 0.15f;
	else if (!is_moving(data))
		;
	else
		phase += 0.04f;
	if (phase > 6.0f)
		phase -= 6.0f;
	draw_totem(data, base_x, anim_pos_y, (int *)data->buffer.addr);
}
