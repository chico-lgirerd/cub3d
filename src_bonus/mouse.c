/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:57:27 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/06 18:57:01 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <stdlib.h>

void	init_mouse(t_data *data)
{
	data->mouse.center_x = data->win_width / 2;
	data->mouse.center_y = data->win_height / 2;
	data->mouse.square_radius = 80;
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr,
		data->mouse.center_x, data->mouse.center_y);
	data->mouse.recentered = 1;
}

int	mouse_handler(int x, int y, t_data *data)
{
	int		dx;
	double	sensi;

	sensi = MOUSE_SENSI;
	if (!data->mouse.recentered)
	{
		dx = x - data->mouse.last_x;
		if (dx != 0)
			turn_camera(&data->player, dx * sensi);
	}
	if (abs(x - data->mouse.center_x) > data->mouse.square_radius
		|| abs(y - data->mouse.center_y) > data->mouse.square_radius)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			data->mouse.center_x, data->mouse.center_y);
		data->mouse.last_x = data->mouse.center_x;
		data->mouse.recentered = 1;
	}
	else
	{
		data->mouse.last_x = x;
		data->mouse.recentered = 0;
	}
	return (0);
}
