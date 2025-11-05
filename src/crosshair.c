/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:00:11 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/05 16:01:00 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"

void	draw_crosshair(t_data *data)
{
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) - 3, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) - 4, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) - 5, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) - 6, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) - 7, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) - 8, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) + 3, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) + 4, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) + 5, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) + 6, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) + 7, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, data->win_width / 2, (data->win_height / 2) + 8, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) - 3, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) - 4, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) - 5, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) - 6, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) - 7, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) - 8, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) + 3, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) + 4, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) + 5, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) + 6, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) + 7, data->win_height / 2, 0xFF0000);
	my_mlx_pixel_put(&data->game_img, (data->win_width / 2) + 8, data->win_height / 2, 0xFF0000);
}
