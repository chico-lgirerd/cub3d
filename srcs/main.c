/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:46 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/08 20:38:45 by tiaperei         ###   ########.fr       */
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

int rgb_to_int(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

void	draw_simple_wall(t_exec_data *data, int x, int draw_start, int draw_end)
{
	int				y;
	int				color;
	t_raycasting	rc;

	rc = data->raycasting;
	if (data->map[rc.map_x][rc.map_y] == 1)
		color = rgb_to_int(128, 128, 128);
	else if (data->map[rc.map_x][rc.map_y] == 2)
		color = rgb_to_int(255, 0, 0);
	else if (data->map[rc.map_x][rc.map_y] == 3)
		color = rgb_to_int(0, 255, 0);
	else if (data->map[rc.map_x][rc.map_y] == 4)
		color = rgb_to_int(0, 0, 255);
	else
		color = rgb_to_int(255, 255, 255);
	y = draw_start;
	while (y < draw_end)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
		y++;
	}
}

void	draw_ceiling_floor(t_exec_data *data, int x, int draw_start, int draw_end)
{
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = rgb_to_int(100, 100, 255);
	floor_color = rgb_to_int(50, 50, 50);
	y = 0;
	while (y < draw_start)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, ceiling_color);
		y++;
	}
	y = draw_end;
	while (y < data->win_height)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, floor_color);
		y++;
	}
}

void	draw_map(t_exec_data *data, int x)
{
	double			wall_x;
	t_player		*player;
	t_raycasting	*rc;
	t_line			*line;

	player = &data->player;
	rc = &data->raycasting;
	line = &data->raycasting.line;
	if (rc->side == 0)
		wall_x = player->pos_y + rc->perp_walldist * rc->raydir_y;
	else
		wall_x = player->pos_x + rc->perp_walldist * rc->raydir_x;
	wall_x -= floor(wall_x);
	line->tex_x = wall_x;
	line->line_height = data->win_height / rc->perp_walldist;
	line->draw_start = -(line->line_height) / 2 + data->win_height / 2;
	line->draw_end = line->line_height / 2 + data->win_height / 2;
	draw_ceiling_floor(data, x, line->draw_start, line->draw_end);
	draw_simple_wall(data, x, line->draw_start, line->draw_end);
}

int render(t_exec_data *data)
{
    int 			x;
	int				hit;
	t_player		*player;
	t_raycasting	*rc;
	t_line			*line;
	
	player = &data->player;
	rc = &data->raycasting;
	line = &data->raycasting.line;
	x = 0;
	//printf("%d\n", data->map[0][0]);
	while (x < data->win_width)
	{
		rc->map_x = (int)player->pos_x;
		rc->map_y = (int)player->pos_y;
		rc->camera_x = 2 * x / (double)data->win_width - 1;
		rc->raydir_x = player->dir_x + player->plane_x * rc->camera_x;
		rc->raydir_y = player->dir_y + player->plane_y * rc->camera_x;
		rc->deltadist_x = fabs(1 / rc->raydir_x); //if raydir_x or raydir_y == 0 (1e30)
		rc->deltadist_y = fabs(1 / rc->raydir_y); //if raydir_x or raydir_y == 0 (1e30)
		if (rc->raydir_x < 0)
		{
			rc->step_x = -1;
			rc->walldist_x = (player->pos_x - rc->map_x) * rc->deltadist_x;
		}
		else
		{
			rc->step_x = 1;
			rc->walldist_x = ((rc->map_x + 1) - player->pos_x) * rc->deltadist_x;
		}
		if (rc->raydir_y < 0)
		{
			rc->step_y = -1;
			rc->walldist_y = (player->pos_y - rc->map_y) * rc->deltadist_y;
		}
		else
		{
			rc->step_y = 1;
			rc->walldist_y = ((rc->map_y + 1) - player->pos_y) * rc->deltadist_y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (rc->walldist_x < rc->walldist_y)
			{
				rc->walldist_x += rc->deltadist_x;
				rc->map_x += rc->step_x;
				rc->side = 0;
			}
			else
			{
				rc->walldist_y += rc->deltadist_y;
				rc->map_y += rc->step_y;
				rc->side = 1;
			}
			if (data->map[rc->map_x][rc->map_y] > 0)
				hit = 1;
		}
		if (rc->side == 0)
			rc->perp_walldist = rc->walldist_x - rc->deltadist_x;
		else
			rc->perp_walldist = rc->walldist_y - rc->deltadist_y;
		draw_map(data, x);
		x++;
	}
	return (0);
}

int	move_front(t_exec_data *data)
{
	t_player		*player;
	t_raycasting	*rc;

	player = &data->player;
	rc = &data->raycasting;	
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
