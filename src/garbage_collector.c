/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:23:12 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/21 15:39:55 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "mlx.h"
#include <stdlib.h>

void	destroy_images(t_world *w, t_textures *textures)
{
	if (textures->north.img)
		mlx_destroy_image(w->mlx_ptr, textures->north.img);
	if (textures->south.img)
		mlx_destroy_image(w->mlx_ptr, textures->south.img);
	if (textures->east.img)
		mlx_destroy_image(w->mlx_ptr, textures->east.img);
	if (textures->west.img)
		mlx_destroy_image(w->mlx_ptr, textures->west.img);
	textures->north.img = NULL;
	textures->south.img = NULL;
	textures->east.img = NULL;
	textures->west.img = NULL;
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
	destroy_images(world, &world->textures);
	mlx_destroy_window(world->mlx_ptr, world->win_ptr);
	mlx_destroy_display(world->mlx_ptr);
	free(world->mlx_ptr);
	free(world);
	world = NULL;
}
