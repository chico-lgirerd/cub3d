/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:46 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/06 22:50:10 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int worldmap[MAP_WIDTH][MAP_HEIGHT] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	init_map(t_exec_data *data)
{
	int	x;
	int	y;
	
	data->map_width = MAP_WIDTH;
	data->map_height = MAP_HEIGHT;
	data->map = malloc(sizeof(int *) * MAP_WIDTH);
	if (!data->map)
		;
	x = 0;
	while (x < MAP_WIDTH)
	{
		data->map[x] = malloc(sizeof(int) * MAP_HEIGHT);
		if (!data->map)
			;
		y = 0;
		while (y < MAP_HEIGHT)
		{
			data->map[x][y] = worldmap[x][y];
			y++;
		}
		x++;
	}
}

void	init_player(t_player *player)
{
	player->pos_x = 20;
	player->pos_y = 20;
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

void draw_block(t_exec_data *data, int x, int y, int color)
{
    int i, j;

    for (i = 0; i < 50; ++i)
        for (j = 0; j < 50; ++j)
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, x * 50 + i, y * 50 + j, color);
}

int render(t_exec_data *data)
{
    int x;
    //int y;
	int	hit;
	t_player	*player;
	t_raycast	*raycast;
 
	player = &data->player;
	raycast = &data->raycast;
	x = 0;
	//printf("%d\n", data->map[0][0]);
	while (x < data->win_width)
	{
		raycast->map_x = (int)player->pos_x;
		raycast->map_y = (int)player->pos_y;
		raycast->camera_x = 2 * x / (double)data->win_width - 1;
		raycast->raydir_x = player->dir_x + player->plane_x * raycast->camera_x;
		raycast->raydir_y = player->dir_y + player->plane_y * raycast->camera_x;
		raycast->deltadist_x = fabs(1 / raycast->raydir_x); //if raydir_x or raydir_y == 0 (1e30)
		raycast->deltadist_x = fabs(1 / raycast->raydir_y); //if raydir_x or raydir_y == 0 (1e30)
		if (raycast->raydir_x < 0)
		{
			raycast->step_x = -1;
			raycast->dist_x = (player->pos_x - raycast->map_x) * raycast->deltadist_x;
		}
		else
		{
			raycast->step_x = 1;
			raycast->dist_x = ((raycast->map_x + 1) - player->pos_x) * raycast->deltadist_x;
		}
		if (raycast->raydir_y < 0)
		{
			raycast->step_y = -1;
			raycast->dist_y = (player->pos_y - raycast->map_y) * raycast->deltadist_y;
		}
		else
		{
			raycast->step_y = 1;
			raycast->dist_y = ((raycast->map_y + 1) - player->pos_y) * raycast->deltadist_y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (raycast->dist_x < raycast->dist_y)
			{
				raycast->dist_x += raycast->deltadist_x;
				raycast->map_x += raycast->step_x;
				raycast->side = 0;
			}
			else
			{
				raycast->dist_y += raycast->deltadist_y;
				raycast->map_y += raycast->step_y;
				raycast->side = 1;
			}
			if (data->map[raycast->map_x][raycast->map_y] > 0)
				hit = 1;
		}
		x++;
	}
	return (0);
}

int	move_front(t_exec_data *data)
{
	int	i;

	i = 0;
	(void)data;
	while (i < 400)
	{
		//draw_wall(data, i + 900);
		i++;
	}
	return (0); 
}

int	handle_input(int keysym, t_exec_data *data)
{
	if (keysym == XK_Escape)
		end_game(data);
	else if (keysym == XK_Up)
		move_front(data);
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
	init_map(&data);
	init_player(&data.player);
	exec_game(&data);
	(void)ac;
	(void)av;
	return (0);
}
