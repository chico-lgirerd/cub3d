/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:57:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/16 17:32:14 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "mlx.h"
#include "libft.h"

#include <stdio.h>

int	is_map_line(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (*line == '0' || *line == '1');
}

void	init_colors(t_world *w)
{
	w->textures.ceiling.red = -1;
	w->textures.ceiling.green = -1;
	w->textures.ceiling.blue = -1;
	w->textures.floor.red = -1;
	w->textures.floor.green = -1;
	w->textures.floor.blue = -1;
}

int	init_world(t_world *world)
{
	world->textures.width = 800;
	world->textures.height = 400;
	init_colors(world);
	world->mlx_ptr = mlx_init();
	world->win_ptr = mlx_new_window(world->mlx_ptr, 800, 400, "test1");
	if (!world->mlx_ptr || !world->win_ptr)
		return (0);
	return (1);
}

void	print_textures(t_textures textures)
{
	printf("North : %p\n", textures.north);
	printf("South : %p\n", textures.south);
	printf("West : %p\n", textures.west);
	printf("East : %p\n", textures.east);
	printf("Ceiling : %d, %d, %d\n", textures.ceiling.red, textures.ceiling.green, textures.ceiling.blue);
	printf("Floor : %d, %d, %d\n", textures.floor.red, textures.floor.green, textures.floor.blue);
}

int	main(int ac, char **av)
{
	t_world	*world1;
	char	**map;
	int		line_idx;

	world1 = malloc(sizeof(t_world));
	if (!world1)
		return (1);
	ft_memset(world1, 0, sizeof(t_world));
	if (!check_args(ac, av))
	{
		free(world1);
		return (1);
	}
	map = NULL;
	map = map_from_file(av[1], map);
	if (!map)
	{
		printf("Error\nCould not get map from file : %s\n", av[1]);
		free(world1);
		return (1);
	}
	world1->map = map;
	if (!init_world(world1))
	{
		free_map(world1->map);
		free(world1);
		return (1);
	}
	line_idx = 0;
	while (map[line_idx] && !is_map_line(map[line_idx]))
	{
		if (get_textures(world1, map[line_idx]))
		{
			free_world(world1);
			return (1);
		}
		line_idx++;
	}
	if (have_textures(world1->textures))
		printf("Parsed all textures\n");
	else
	{
		free_world(world1);
		return (1);
	}
	if (!handle_map_error(is_valid_map(map, line_idx)))
		printf("------- MAP IS VALID -------\n");
	print_textures(world1->textures);
	free_world(world1);
	return (0);
}
