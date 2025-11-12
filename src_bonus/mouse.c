/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:57:27 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/12 15:22:28 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>

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

int	ingame_mouse(int x, int y, t_data *data)
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

int	inpause_mouse(t_data *data)
{
	mlx_mouse_show(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	mouse_handler(int x, int y, t_data *data)
{
	if (data->key.key_pause)
		inpause_mouse(data);
	else
	{
		mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
		ingame_mouse(x, y, data);
	}
	return (0);
}

int	mouse_button_handler(int button, int x, int y, t_data *data)
{
	double	step;
	double	i;
	int		map_x;
	int		map_y;

	(void)x, (void)y;
	step = 0.01;
	i = 0;
	if (button == 1)
	{
		while (i < INTERACT_RADIUS)
		{
			map_x = (int)floor(data->player.pos_x + data->player.dir_x * i);
			map_y = (int)floor(data->player.pos_y + data->player.dir_y * i);
			if (data->map[map_y][map_x] == 'D')
			{
				data->raycasting.door.is_open = !data->raycasting.door.is_open;
				break ;
			}
			i += step;
		}
	}
	return (1);
}
