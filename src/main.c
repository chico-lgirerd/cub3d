/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:46 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/26 19:00:55 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>

int	end_game(t_exec_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
	// return (0);
}

int	render(t_exec_data *data)
{
	struct timeval	curr_time;
	static struct timeval	last_time;
	static int	frame_count;
	static struct timeval last_check = {0, 0};

	gettimeofday(&curr_time, NULL);
	if (last_check.tv_sec == 0 && last_check.tv_usec == 0)
        last_check = curr_time;
	frame_count++;
	double elapsed = (curr_time.tv_sec - last_check.tv_sec)
                  + (curr_time.tv_usec - last_check.tv_usec) / 1000000.0;
    if (elapsed >= 1.0)
	{
        printf("FPS: %d\n", frame_count);
        frame_count = 0;
        last_check = curr_time;
    }
	update_player(data, curr_time, last_time);
	last_time = curr_time;
	draw_minimap(data);
	perform_raycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->game_img.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->minimap_img.img_ptr, 0, 0);
	return (0);
}

void	exec_game(t_exec_data *data)
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
	mlx_hook(data->win_ptr, DestroyNotify, 0, &end_game, data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_loop(data->mlx_ptr);
	end_game(data);
}

int	main(int ac, char **av)
{
	t_exec_data	data;

	if (ac != 2)
	{
		printf("Error\nUsage : ./cubed <filename.cub>\n");
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_exec_data));
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	if (init_map(&data, av[1]))
		return (1);
	init_player(&data.player);
	exec_game(&data);
	return (0);
}
