/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:09:39 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/19 16:21:17 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>

static void	fps_counter(t_data *data, struct timeval curr_time)
{
	static int				frame_count;
	static struct timeval	last_check;
	double					elapsed;
	char					fps_str[32];
	static int				fps;

	if (last_check.tv_sec == 0 && last_check.tv_usec == 0)
		last_check = curr_time;
	frame_count++;
	elapsed = (curr_time.tv_sec - last_check.tv_sec)
		+ (curr_time.tv_usec - last_check.tv_usec) / 1000000.0;
	if (elapsed >= 0.5)
	{
		fps = frame_count * 2;
		frame_count = 0;
		last_check = curr_time;
	}
	snprintf(fps_str, sizeof(fps_str), "FPS : %d", fps);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 1865, 20, 0xFFFFFF, fps_str);
}

static int	render(t_data *data)
{
	struct timeval			curr_time;
	static struct timeval	last_time;

	gettimeofday(&curr_time, NULL);
	update_player(data, curr_time, last_time);
	last_time = curr_time;
	perform_rays(data);
	draw_minimap(data);
	draw_crosshair(data);
	animate_pickaxe(data, 1300, 600);
	animate_totem(data, 30, 650);
	if (data->key.key_pause)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->pause.img_ptr, 0, 0);
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->buffer.img_ptr, 0, 0);
	fps_counter(data, curr_time);
	return (0);
}

void	exec_game(t_data *data)
{
	mlx_get_screen_size(data->mlx_ptr, &data->win_width, &data->win_height);
	data->minimap.width = data->win_height / 6;
	data->minimap.height = data->win_height / 6;
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width, data->win_height, "cub3D");
	if (!data->win_ptr)
		secure_free(data);
	init_image(data);
	init_mouse(data);
	init_pickaxe(data);
	init_totem(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->win_ptr, MotionNotify, 1L << 6, mouse_handler, data);
	mlx_mouse_hook(data->win_ptr, &mouse_button_handler, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, &secure_free, data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_loop(data->mlx_ptr);
	secure_free(data);
}
