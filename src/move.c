/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:24:51 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/05 13:37:14 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	move_forward(t_data *data, t_player *player, float speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * speed;
	new_y = player->pos_y + player->dir_y * speed;
	if (data->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

void	move_backward(t_data *data, t_player *player, float speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * speed;
	new_y = player->pos_y - player->dir_y * speed;
	if (data->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

void	move_left(t_data *data, t_player *player, float speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->plane_x * speed;
	new_y = player->pos_y - player->plane_y * speed;
	if (data->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

void	move_right(t_data *data, t_player *player, float speed)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->plane_x * speed;
	new_y = player->pos_y + player->plane_y * speed;
	if (data->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}
