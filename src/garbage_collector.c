/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:23:12 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/20 09:37:07 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "mlx.h"
#include <stdlib.h>

void	destroy_images(t_world *world, t_textures textures)
{
	if (textures.north)
		mlx_destroy_image(world->mlx_ptr, textures.north);
	if (textures.south)
		mlx_destroy_image(world->mlx_ptr, textures.south);
	if (textures.east)
		mlx_destroy_image(world->mlx_ptr, textures.east);
	if (textures.west)
		mlx_destroy_image(world->mlx_ptr, textures.west);
	textures.north = NULL;
	textures.south = NULL;
	textures.east = NULL;
	textures.west = NULL;
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

void	free_world(t_world *world)
{
	if (!world)
		return ;
	free_map(world->map);
	destroy_images(world, world->textures);
	mlx_destroy_window(world->mlx_ptr, world->win_ptr);
	mlx_destroy_display(world->mlx_ptr);
	free(world->mlx_ptr);
	free(world);
	world = NULL;
}
