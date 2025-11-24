/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:06:00 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/24 19:23:58 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	get_texture_color(t_wall *texture, int tex_x, int tex_y)
{
	int				bytes_per_pixel;
	int				offset;
	unsigned char	*pixel;
	int				color;

	bytes_per_pixel = texture->bpp / 8;
	offset = tex_y * texture->length + tex_x * bytes_per_pixel;
	pixel = (unsigned char *)texture->addr + offset;
	color = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16) | (pixel[3] << 24);
	return (color);
}

int	map_in_border(t_data *data, int map_x, int map_y)
{
	return (map_y >= data->map_start && map_y <= data->map_end
		&& map_x >= 0 && map_x < (int)ft_strlen(data->map[map_y]) - 1);
}
