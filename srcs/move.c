/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:24:51 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/22 13:33:48 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	move_forward(t_exec_data *data, t_player *player, float speed)
{
	(void)data;
	player->pos_x += player->dir_x * speed;
	player->pos_y += player->dir_y * speed;
}

void	move_backward(t_exec_data *data, t_player *player, float speed)
{
	(void)data;
	player->pos_x -= player->dir_x * speed;
	player->pos_y -= player->dir_y * speed;
}

void	move_left(t_exec_data *data, t_player *player, float speed)
{
	(void)data;
	player->pos_x -= player->plane_x * speed;
	player->pos_y -= player->plane_y * speed;
}

void	move_right(t_exec_data *data, t_player *player, float speed)
{
	(void)data;
	player->pos_x += player->plane_x * speed;
	player->pos_y += player->plane_y * speed;
}
