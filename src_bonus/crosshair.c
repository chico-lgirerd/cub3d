/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:00:11 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/19 20:26:55 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <math.h>

void	draw_crosshair(t_data *data)
{
	static float	phase = 0.0f;
	int				length;
	int				px;
	int				py;
	int				offset;

	length = 8 + (int)(sin(phase) * 4);
	offset = 3;
	px = data->win_width / 2;
	py = data->win_height / 2;
	phase += 0.02f;
	while (offset <= length)
	{
		my_mlx_pixel_put(&data->buffer, px, py - offset, 0xFF0000);
		my_mlx_pixel_put(&data->buffer, px, py + offset, 0xFF0000);
		my_mlx_pixel_put(&data->buffer, px - offset, py, 0xFF0000);
		my_mlx_pixel_put(&data->buffer, px + offset, py, 0xFF0000);
		offset++;
	}
}
