/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:46 by tiaperei          #+#    #+#             */
/*   Updated: 2025/09/30 18:16:26 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>


void	draw_wall(t_exec_data *data, int x)
{
	int	wall_height;
	int	start;
	int	end;
	int	y;
	
	wall_height = data->win_height / 10;
	start = (data->win_height - wall_height) / 2;
	end = start + wall_height;
	y = start;
	while (y < end)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00FF0000);
		y++;
	}
}

int	render(t_exec_data *data)
{
	draw_wall(data, 1000);
	return (0); 
}
int	handle_input(int keysym, t_exec_data *data)
{
	if (keysym == XK_Escape)
		end_game(data);
	return (0);
}

int	end_game(t_exec_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
	//return (0);
}

void	exec_game(t_exec_data *data)
{
	mlx_get_screen_size(data->mlx_ptr, &data->win_width, &data->win_height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_height, "cub3D");
	if (!data->win_ptr)
		;
	mlx_key_hook(data->win_ptr, &handle_input, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, &end_game, data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_loop(data->mlx_ptr);
	end_game(data);
}

int	main(int ac, char **av)
{
	t_exec_data	data;
	
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		;
	exec_game(&data);
	(void)ac;
	(void)av;
	return (0);
}
