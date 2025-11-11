/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:09:39 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/10 22:51:54 by lgirerd          ###   ########lyon.fr   */
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

	(void)data;
	if (last_check.tv_sec == 0 && last_check.tv_usec == 0)
		last_check = curr_time;
	frame_count++;
	elapsed = (curr_time.tv_sec - last_check.tv_sec)
		+ (curr_time.tv_usec - last_check.tv_usec) / 1000000.0;
	if (elapsed >= 1.0)
	{
		printf("FPS: %d\n", frame_count);
		frame_count = 0;
		last_check = curr_time;
	}
}

// static int	pause(t_data *data)
// {
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
// 		data->pause.img_ptr, 0, 0);
// 	if (data->key.key_pause)
// 		return (1);
// 	return (0);
// }

static int	render(t_data *data)
{
	struct timeval			curr_time;
	static struct timeval	last_time;

	gettimeofday(&curr_time, NULL);
	fps_counter(data, curr_time);
	update_player(data, curr_time, last_time);
	last_time = curr_time;
	draw_minimap(data);
	perform_raycasting(data);
	draw_crosshair(data);
	animate_pickaxe(data, 1300, 600);
	animate_totem(data, 30, 650);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->game_img.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->minimap_img.img_ptr, 10, 10);
	if (data->key.key_pause)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->pause.img_ptr, 0, 0);
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
	init_pause(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->win_ptr, MotionNotify, 1L << 6, mouse_handler, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, &secure_free, data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_loop(data->mlx_ptr);
	secure_free(data);
}
