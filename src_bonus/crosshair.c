/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:00:11 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/05 17:08:30 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <math.h>

void	draw_crosshair(t_data *data)
{
	static float	phase = 0.0f;
	int				base_len = 8;
	int				anim_range = 4;
	int				length = base_len + (int)(sin(phase) * anim_range);
	int				px = data->win_width / 2;
	int				py = data->win_height / 2;

	phase += 0.02f;
	int	offset = 3;
	while (offset <= length)
	{
		my_mlx_pixel_put(&data->game_img, px, py - offset, 0xFF0000);
		my_mlx_pixel_put(&data->game_img, px, py + offset, 0xFF0000);
		my_mlx_pixel_put(&data->game_img, px - offset, py, 0xFF0000);
		my_mlx_pixel_put(&data->game_img, px + offset, py, 0xFF0000);
		offset++;
	}
}
