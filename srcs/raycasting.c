/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:55:39 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/17 19:18:28 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <math.h>
//#include <stdio.h>

int perform_raycasting(t_exec_data *data)
{
	int 			x;
	int				hit;
	t_player		*player;
	t_raycasting	*rc;
	
	player = &data->player;
	rc = &data->raycasting;
	x = 0;
	while (x < data->win_width)
	{
		rc->map_x = (int)player->pos_x;
		rc->map_y = (int)player->pos_y;
		rc->camera_x = 2 * x / (double)data->win_width - 1;
		rc->raydir_x = player->dir_x + player->plane_x * rc->camera_x;
		rc->raydir_y = player->dir_y + player->plane_y * rc->camera_x;
		//printf("raydir_x = %f + %f * %f = %f\n", player->dir_x, player->plane_x, rc->camera_x, rc->raydir_x);	
		if (rc->raydir_x == 0)
			rc->deltadist_x = 1e30;
		else
			rc->deltadist_x = fabs(1 / rc->raydir_x);
		if (rc->raydir_y == 0)
			rc->deltadist_y = 1e30;
		else
			rc->deltadist_y = fabs(1 / rc->raydir_y);
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
		//printf("wall_dist_y = %f\n", rc->walldist_y);
		//printf("wall_dist_x = %f\n", rc->walldist_x);
		//printf("map_x = %d\n", rc->map_x);
		//printf("map_y = %d\n", rc->map_y);
		hit = 0;
		while (hit == 0 && rc->map_x >= 0 && rc->map_x < data->map_width
			&& rc->map_y >= 0 && rc->map_y < data->map_height)
		{
			if (rc->walldist_x < rc->walldist_y)
			{
				rc->walldist_x += rc->deltadist_x;
				rc->map_x += rc->step_x;
				rc->side = 0;
			}
			else
			{
				//printf("wall_dist_y = %f\n", rc->walldist_y);
				//printf("map_y before = %d\n", rc->map_y);
				rc->walldist_y += rc->deltadist_y;
				rc->map_y += rc->step_y;
				rc->side = 1;
			}
			if (data->map[rc->map_y][rc->map_x] > 0)
				hit = 1;
			//printf("data->map[%d][%d] = %d\n", rc->map_y, rc->map_x, data->map[rc->map_y][rc->map_x]);
		}
		if (rc->side == 0)
    		rc->perp_walldist = (rc->map_x - player->pos_x + (1 - rc->step_x) / 2) / rc->raydir_x;
		else
   			rc->perp_walldist = (rc->map_y - player->pos_y + (1 - rc->step_y) / 2) / rc->raydir_y;
		if (x == data->win_width / 2)
			draw_ray_minimap(data);
		draw_map(data, x);
		x++;
	}
	return (0);
}