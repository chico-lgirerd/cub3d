/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:55:39 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/19 15:20:09 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <math.h>

static void	init_raycasting(t_data *data, int x)
{
	t_player		*player;
	t_raycasting	*rc;

	player = &data->player;
	rc = &data->raycasting;
	rc->hit = 0;
	rc->door_seen = 0;
	rc->map_x = (int)player->pos_x;
	rc->map_y = (int)player->pos_y;
	rc->camera_x = 2 * x / (double)data->win_width - 1;
	rc->raydir_x = player->dir_x + player->plane_x * rc->camera_x;
	rc->raydir_y = player->dir_y + player->plane_y * rc->camera_x;
	if (rc->raydir_x == 0)
		rc->deltadist_x = 1e30;
	else
		rc->deltadist_x = fabs(1 / rc->raydir_x);
	if (rc->raydir_y == 0)
		rc->deltadist_y = 1e30;
	else
		rc->deltadist_y = fabs(1 / rc->raydir_y);
}

static void	calcul_dist_next_cases(t_data *data)
{
	t_player		*player;
	t_raycasting	*rc;

	player = &data->player;
	rc = &data->raycasting;
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
}

static void	perform_dda(t_data *data)
{
	t_raycasting	*rc;

	rc = &data->raycasting;
	while (rc->hit == 0)
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
		if (data->map[rc->map_y][rc->map_x] == '1'
				|| data->map[rc->map_y][rc->map_x] == 'D')
			rc->hit = 1;
	}
}

static int	ray_hit_door(t_data *data)
{
	t_player		*player;
	t_raycasting	*rc;

	player = &data->player;
	rc = &data->raycasting;
	rc->tmpdoor = get_door_from_pos(data,
			rc->map_y - data->map_start + 1, rc->map_x);
	if (rc->side == 0)
		rc->tmpdoor->pos = player->pos_y + rc->perp_walldist * rc->raydir_y;
	else
		rc->tmpdoor->pos = player->pos_x + rc->perp_walldist * rc->raydir_x;
	rc->tmpdoor->pos -= floor(rc->tmpdoor->pos);
	if (!rc->tmpdoor->is_open || (rc->tmpdoor->pos >= rc->tmpdoor->open_pos
			&& rc->tmpdoor->pos <= rc->tmpdoor->open_pos + rc->tmpdoor->width))
		return (1);
	else
		return (0);
}

int	perform_raycasting(t_data *data)
{
	t_player		*player;
	t_raycasting	*rc;
	int				x;

	player = &data->player;
	rc = &data->raycasting;
	x = 0;
	while (x < data->win_width)
	{
		init_raycasting(data, x);
		calcul_dist_next_cases(data);
		perform_dda(data);
		if (rc->side == 0)
			rc->perp_walldist = (rc->map_x - player->pos_x
					+ (1 - rc->step_x) / 2) / rc->raydir_x;
		else
			rc->perp_walldist = (rc->map_y - player->pos_y
					+ (1 - rc->step_y) / 2) / rc->raydir_y;
		if (data->map[rc->map_y][rc->map_x] == 'D' && ray_hit_door(data))
			rc->door_seen = 1;
		draw_map(data, x);
		x++;
	}
	return (0);
}
