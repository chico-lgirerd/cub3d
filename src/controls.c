/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:17:10 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/05 17:24:53 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <math.h>

static void	turn_left(t_player *player, double rot)
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

static void	turn_right(t_player *player, double rot)
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

int	key_press(int keycode, t_data *data)
{
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
	if (keycode == 65505)
		data->key.key_sprint = 1;
	if (keycode == 65307)
		secure_free(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
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
	if (keycode == 65505)
		data->key.key_sprint = 0;
	return (0);
}

void	update_player(t_data *data, struct timeval curr_time,
	struct timeval last_time)
{
	double		delta;
	double		speed;
	double		rot;
	t_player	*player;

	delta = ((curr_time.tv_sec * 1000000L + curr_time.tv_usec)
			- (last_time.tv_sec * 1000000L + last_time.tv_usec)) / 1000000.0;
	speed = BASE_SPEED * delta;
	if (data->key.key_sprint)
		speed *= 2.5;
	rot = BASE_SENSI * delta;
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
