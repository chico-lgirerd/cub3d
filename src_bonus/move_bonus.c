/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:24:51 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/19 21:48:49 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static int	is_walkable(t_data *data, int x, int y)
{
	if (y < data->map_start || y > data->map_end)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(data->map[y]))
		return (0);
	if (data->map[y][x] == '0')
		return (1);
	if (data->map[y][x] == 'D')
		if (get_door_state(data, y - data->map_start + 1, x) == 1)
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
