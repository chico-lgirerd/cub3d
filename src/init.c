/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:42:08 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/20 09:44:21 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

void	init_colors(t_world *w)
{
	w->textures.ceiling.red = -1;
	w->textures.ceiling.green = -1;
	w->textures.ceiling.blue = -1;
	w->textures.floor.red = -1;
	w->textures.floor.green = -1;
	w->textures.floor.blue = -1;
}

t_world	*init_world(void)
{
	t_world	*w;

	w = malloc(sizeof(t_world));
	if (!w)
		return (NULL);
	ft_memset(w, 0, sizeof(t_world));
	w->textures.width = 800;
	w->textures.height = 400;
	init_colors(w);
	w->mlx_ptr = mlx_init();
	w->win_ptr = mlx_new_window(w->mlx_ptr, 800, 400, "test1");
	if (!w->mlx_ptr || !w->win_ptr)
		return (NULL);
	return (w);
}

int	init_parsing(t_world *world, char *filename)
{
	int	line_idx;

	world->map = map_from_file(filename);
	if (!world->map)
	{
		printf("Error\nCould not get map from file : %s\n", filename);
		free(world);
		return (1);
	}
	line_idx = 0;
	while (world->map[line_idx] && !is_map_line(world->map[line_idx]))
	{
		if (get_textures(world, world->map[line_idx]))
		{
			free_world(world);
			return (1);
		}
		line_idx++;
	}
	world->map_start = line_idx;
	return (0);
}
