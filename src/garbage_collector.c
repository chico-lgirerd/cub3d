/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_garbageman.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:22:21 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/04 15:27:36 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"
#include <stdlib.h>

void	destroy_images(void *mlx_ptr, t_textures *txs)
{
	if (txs->north.img)
		mlx_destroy_image(mlx_ptr, txs->north.img);
	if (txs->south.img)
		mlx_destroy_image(mlx_ptr, txs->south.img);
	if (txs->east.img)
		mlx_destroy_image(mlx_ptr, txs->east.img);
	if (txs->west.img)
		mlx_destroy_image(mlx_ptr, txs->west.img);
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