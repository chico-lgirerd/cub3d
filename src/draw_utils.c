/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:06:00 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/22 14:02:47 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <stdlib.h>

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void draw_ray_minimap(t_exec_data *data)
{
	t_raycasting	*rc = &data->raycasting;
    t_player 		*player = &data->player;
    int scale = data->minimap_width / data->map_width;
	int x0 = (int)(player->pos_x * scale);
	int y0 = (int)(player->pos_y * scale);
	int x1 = (int)((player->pos_x + rc->perp_walldist * rc->raydir_x) * scale);
	int y1 = (int)((player->pos_y + rc->perp_walldist * rc->raydir_y) * scale);

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        my_mlx_pixel_put(&data->minimap_img, x0, y0, rgb_to_int(0, 255, 0));
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}
