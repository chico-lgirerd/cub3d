/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:57:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/06 22:07:21 by lgirerd          ###   ########lyon.fr   */
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
    return *line == '0' || *line == '1';
}

void	init_world(t_world *world)
{
	world->textures.width = 800;
	world->textures.height = 400;
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
	t_world	world1;
	char	**map;

	ft_memset(&world1, 0, sizeof(t_world));

	if (!check_args(ac, av))
		return (1);
	map = NULL;
	map = map_from_file(&world1, av[1], map);
	for (int i = 0; map[i]; i++)
		printf("%s", map[i]);
	printf("\n");
	world1.mlx_ptr = mlx_init();
	world1.win_ptr = mlx_new_window(world1.mlx_ptr, 800, 400, "test1");
	world1.map = map;
	init_world(&world1);
	int	line_idx = 0;
	while (map[line_idx] && !is_map_line(map[line_idx]))
	{
		printf("line_idx : %d\n", line_idx);
		if (get_textures(&world1, map[line_idx]))
			return (1);
		line_idx++;
		
	}
	if (have_textures(world1.textures))
		printf("Parsed all textures !\n");
	print_textures(world1.textures);
	return (0);
}
