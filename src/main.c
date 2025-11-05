/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:46 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/05 14:00:04 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>

void	fps_counter(t_data *data, struct timeval curr_time)
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

int	render(t_data *data)
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->game_img.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->minimap_img.img_ptr, 10, 10);
	return (0);
}

void	exec_game(t_data *data)
{
	mlx_get_screen_size(data->mlx_ptr, &data->win_width, &data->win_height);
	data->minimap_width = data->win_height / 6;
	data->minimap_height = data->win_height / 6;
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width, data->win_height, "cub3D");
	if (!data->win_ptr)
		return ;
	init_image(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, &secure_free, data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_loop(data->mlx_ptr);
	secure_free(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	if (init_map(&data, av[1]))
	{
		secure_free(&data);
		return (1);
	}
	init_player(&data.player);
	exec_game(&data);
	return (0);
}
