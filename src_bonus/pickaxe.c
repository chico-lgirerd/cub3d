/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:45:45 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/10 18:30:39 by lgirerd          ###   ########lyon.fr   */
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
		"assets/pickaxe500.xpm", &data->pickaxe.width, &data->pickaxe.height);
	data->pickaxe.addr = mlx_get_data_addr(data->pickaxe.img_ptr,
		&data->pickaxe.bits_per_pixel, &data->pickaxe.size_line,
		&data->pickaxe.endian);
}

void	animate_pickaxe(t_data *data, int base_x, int base_y)
{
	static float	phase = 0.0f;
	int				offset_y;
	int				anim_pos_y;

	offset_y = (int)(sin(phase) * 8);
	anim_pos_y = base_y + offset_y;
	phase += 0.04f;
	if (phase > 6.283185f)
		phase -= 6.283185f;
	draw_pickaxe(data, base_x, anim_pos_y);
}


void	draw_pickaxe(t_data *data, int pos_x, int pos_y)
{
	int	x;
	int	y;
	int	*p_data;
	int	*game_data;
	int color;
	
	p_data = (int *)data->pickaxe.addr;
	game_data = (int *)data->game_img.addr;
	
	y = 0;
	while (y < data->pickaxe.height)
	{
		x = 0;
		while (x < data->pickaxe.width)
		{
			color = p_data[y * (data->pickaxe.size_line / 4) + x];
			if ((color & 0x00FFFFFF) != 0x000000)
			{
				if (pos_x + x >= 0 && pos_x + x < data->game_img.width && 
					pos_y + y >= 0 && pos_y + y < data->game_img.height)
				game_data[(pos_y + y) * (data->game_img.size_line / 4) + (pos_x + x)] = color;
				// my_mlx_pixel_put(&data->game_img, x, y, color);
			}
			x++;
		}
		y++;
	}
}