/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:24:51 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/31 11:51:47 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	move_forward(t_data *data, t_player *player, float speed)
{
	double new_x;
	double new_y;
	
	new_x = player->pos_x + player->dir_x * speed;
	new_y = player->pos_y + player->dir_y * speed;
	if (data->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

void	move_backward(t_data *data, t_player *player, float speed)
{
	double new_x;
	double new_y;

	new_x = player->pos_x - player->dir_x * speed;
	new_y = player->pos_y - player->dir_y * speed;
	if (data->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

void	move_left(t_data *data, t_player *player, float speed)
{
	double new_x;
	double new_y;
	
	new_x = player->pos_x - player->plane_x * speed;
	new_y = player->pos_y - player->plane_y * speed;
	if (data->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

void	move_right(t_data *data, t_player *player, float speed)
{
	double new_x;
	double new_y;

	new_x = player->pos_x + player->plane_x * speed;
	new_y = player->pos_y + player->plane_y * speed;
	// #include <stdio.h>
	// printf("player_new_x : %d\n", (int)new_x);
	// printf("player_pos_x : %d\n", (int)player->pos_x);
	// printf("player_new_y : %d\n", (int)new_y);
	// printf("player_pos_y : %d\n", (int)player->pos_y);
	if (data->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (data->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}
