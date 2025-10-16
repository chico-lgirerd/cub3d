/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:06:00 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/16 16:04:10 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../minilibx-linux/mlx.h"
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

void	draw_ray_minimap(t_exec_data *data, double ray_end_x, double ray_end_y)
{
	int scale = 20; // taille d'une case	
	int start_x = (int)(data->player.pos_x * scale);
	int start_y = (int)(data->player.pos_y * scale);
	//printf("ray_end_x = %f\n", ray_end_x);
	//printf("ray_end_y = %f\n", ray_end_y);
	int end_x = (int)(ray_end_x * scale);
	int end_y = (int)(ray_end_y * scale);

	int dx = end_x - start_x;
	int dy = end_y - start_y;

	int steps;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);

	if (steps == 0)
		return;

	double x_inc = dx / (double)steps;
	double y_inc = dy / (double)steps;

	double x = (double)start_x;
	double y = (double)start_y;

	int i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)x, (int)y, rgb_to_int(0,255,0));
		x += x_inc;
		y += y_inc;
		i++;
	}
}
