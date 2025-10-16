/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:46 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/16 19:30:58 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../libft/include/libft.h"
#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <stdlib.h>

int	end_game(t_exec_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);
	//return (0);
}

int	render(t_exec_data *data)
{
	update_player(data);
	perform_raycasting(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

void	exec_game(t_exec_data *data)
{
	mlx_get_screen_size(data->mlx_ptr, &data->win_width, &data->win_height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_height, "cub3D");
	if (!data->win_ptr)
		;
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
	
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		;
	init_map(&data);
	init_player(&data.player);
	ft_memset(&data.key, 0, sizeof(t_key));
	exec_game(&data);
	(void)ac;
	(void)av;
	return (0);
}
