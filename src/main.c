/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:46 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/04 16:14:00 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>

int	end_game(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
	// return (0);
}

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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->game_img.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->minimap_img.img_ptr, 10, 10);
	return (0);
}

int	mouse_handler(int x, int y, t_data *data)
{
	int		dx;
	double	sensi;

	data->mouse.center_x = data->win_width / 2;
	data->mouse.center_y = data->win_height / 2;
	data->mouse.square_radius = 80;
	dx = x - data->mouse.last_x;
	sensi = 0.002;
	if (dx != 0)
		turn_camera(&data->player, dx * sensi);
	if (abs(x - data->mouse.center_x) > data->mouse.square_radius
		|| abs(y - data->mouse.center_y) > data->mouse.square_radius)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			data->mouse.center_x, data->mouse.center_y);
		data->mouse.last_x = data->mouse.center_x;
	}
	else
		data->mouse.last_x = x;
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
		return ;
	init_image(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->win_ptr, MotionNotify, 1L<<6, mouse_handler, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, &end_game, data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_loop(data->mlx_ptr);
	end_game(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		printf("Error\nUsage : ./cubed <filename.cub>\n");
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	if (init_map(&data, av[1]))
		return (1);
	init_player(&data.player);
	exec_game(&data);
	return (0);
}
