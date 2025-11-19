/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:45:45 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/19 15:50:17 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <math.h>

void	init_pickaxe(t_data *data)
{
	data->pickaxe.width = 512;
	data->pickaxe.height = 512;
	data->pickaxe.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/pickaxe500.xpm",
			&data->pickaxe.width, &data->pickaxe.height);
	data->pickaxe.addr = mlx_get_data_addr(data->pickaxe.img_ptr,
			&data->pickaxe.bits_per_pixel, &data->pickaxe.size_line,
			&data->pickaxe.endian);
}

void	draw_pickaxe(t_data *data, int pos_x, int pos_y, int *image)
{
	int	x;
	int	y;
	int	*p_data;
	int	color;

	p_data = (int *)data->pickaxe.addr;
	y = 0;
	while (y < data->pickaxe.height)
	{
		x = 0;
		while (x < data->pickaxe.width)
		{
			color = p_data[y * (data->pickaxe.size_line / 4) + x];
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

void	animate_pickaxe(t_data *data, int base_x, int base_y)
{
	static float	phase = 0.0f;
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
	if (phase > 6.283185f)
		phase -= 6.283185f;
	draw_pickaxe(data, base_x, anim_pos_y, (int *)data->buffer.addr);
}

int	is_moving(t_data *data)
{
	return (data->key.key_forward || data->key.key_backward
		|| data->key.key_left || data->key.key_right);
}
