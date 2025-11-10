/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:22:21 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/10 19:19:06 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <stdlib.h>

void	destroy_images(t_data *data, void *mlx_ptr, t_textures *txs)
{
	if (txs->north.img)
		mlx_destroy_image(mlx_ptr, txs->north.img);
	if (txs->south.img)
		mlx_destroy_image(mlx_ptr, txs->south.img);
	if (txs->east.img)
		mlx_destroy_image(mlx_ptr, txs->east.img);
	if (txs->west.img)
		mlx_destroy_image(mlx_ptr, txs->west.img);
	if (data->game_img.img_ptr)
		mlx_destroy_image(mlx_ptr, data->game_img.img_ptr);
	if (data->minimap_img.img_ptr)
		mlx_destroy_image(mlx_ptr, data->minimap_img.img_ptr);
	if (data->pickaxe.img_ptr)
		mlx_destroy_image(mlx_ptr, data->pickaxe.img_ptr);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

int	secure_free(t_data *data)
{
	destroy_images(data, data->mlx_ptr, &data->textures);
	if (data->map)
		free_map(data->map);
	if (data->mlx_ptr && data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(EXIT_SUCCESS);
	}
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
