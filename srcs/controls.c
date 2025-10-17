/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:17:10 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/17 16:42:51 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
//#include "../minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

void	move_forward(t_exec_data *data, t_player *player, float speed)
{
	//float	new_x;
	//float	new_y;
	(void)data;

	player->pos_x += player->dir_x * speed;
	player->pos_y += player->dir_y * speed;
}

void	move_backward(t_exec_data *data, t_player *player, float speed)
{
	//float	new_x;
	//float	new_y;
	(void)data;

	player->pos_x -= player->dir_x * speed;
	player->pos_y -= player->dir_y * speed;
}

void	move_left(t_exec_data *data, t_player *player, float speed)
{
	//float	new_x;
	//float	new_y;
	(void)data;

	player->pos_x -= player->plane_x * speed;
	player->pos_y -= player->plane_y * speed;
}

void	move_right(t_exec_data *data, t_player *player, float speed)
{
	//float	new_x;
	//float	new_y;
	(void)data;

	player->pos_x += player->plane_x * speed;
	player->pos_y += player->plane_y * speed;
}

void	turn_left(t_player *player, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-rot) - player->dir_y * sin(-rot);
	player->dir_y = old_dir_x * sin(-rot) + player->dir_y * cos(-rot);
	player->plane_x = player->plane_x * cos(-rot) - player->plane_y * sin(-rot);
	player->plane_y = old_plane_x * sin(-rot) + player->plane_y * cos(-rot);
}

void	turn_right(t_player *player, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dir_x * sin(rot) + player->dir_y * cos(rot);
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_plane_x * sin(rot) + player->plane_y * cos(rot);
}



int	key_press(int keycode, t_exec_data *data)
{
	//printf("keycode = %d\n", keycode);
	if (keycode == 119 || keycode == 65362)
		data->key.key_forward = 1;
	if (keycode == 115 || keycode == 65364)
		data->key.key_backward = 1;
	if (keycode == 97)
		data->key.key_left = 1;
	if (keycode == 100)
		data->key.key_right = 1;
	if (keycode == 65361)
		data->key.key_turn_left = 1;
	if (keycode == 65363)
		data->key.key_turn_right = 1;
	if (keycode == 65307)
		end_game(data);
	return (0);
}

int	key_release(int keycode, t_exec_data *data)
{
	if (keycode == 119 || keycode == 65362)
		data->key.key_forward = 0;
	if (keycode == 115 || keycode == 65364)
		data->key.key_backward = 0;
	if (keycode == 97)
		data->key.key_left = 0;
	if (keycode == 100)
		data->key.key_right = 0;
	if (keycode == 65361)
		data->key.key_turn_left = 0;
	if (keycode == 65363)
		data->key.key_turn_right = 0;
	return (0);
}

void	update_player(t_exec_data *data)
{
	double		speed;
	double		rot;
	t_player	*player;

	speed = 0.3;
	rot = 0.1;
	player = &data->player;
	if (data->key.key_forward)
		move_forward(data, player, speed);
	if (data->key.key_backward)
		move_backward(data, player, speed);
	if (data->key.key_left)
		move_left(data, player, speed);
	if (data->key.key_right)
		move_right(data, player, speed);
	if (data->key.key_turn_left)
		turn_left(player, rot);
	if (data->key.key_turn_right)
		turn_right(player, rot);
}