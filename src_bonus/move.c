/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:24:51 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/19 13:46:18 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	is_walkable(t_data *data, int x, int y)
{
	if (data->map[y][x] == '0')
		return (1);
	if (data->map[y][x] == 'D')
		if (get_door_state(data, x, y) == 1)
			return (1);
	return (0);
}

void	move_forward(t_data *data, t_player *player, float speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * speed;
	new_y = player->pos_y + player->dir_y * speed;
	if (is_walkable(data, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (is_walkable(data, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y; 
}

void	move_backward(t_data *data, t_player *player, float speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * speed;
	new_y = player->pos_y - player->dir_y * speed;
	if (is_walkable(data, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (is_walkable(data, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

void	move_left(t_data *data, t_player *player, float speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->plane_x * speed;
	new_y = player->pos_y - player->plane_y * speed;
	if (is_walkable(data, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (is_walkable(data, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

void	move_right(t_data *data, t_player *player, float speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->plane_x * speed;
	new_y = player->pos_y + player->plane_y * speed;
	if (is_walkable(data, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (is_walkable(data, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y; 
}

int	is_moving(t_data *data)
{
	return (data->key.key_forward || data->key.key_backward
		|| data->key.key_left || data->key.key_right);
}
