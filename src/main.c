/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:57:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/05 20:50:35 by lgirerd          ###   ########lyon.fr   */
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
	int	line_idx = 0;
	while (map[line_idx])
	{
		if (is_map_line(map[line_idx])) {
			printf("Out of loop index : %d\n", line_idx);
			break ;
		}
		if (!get_textures(&world1, map[line_idx]))
			return (1);
		line_idx++;
	}
	if (have_textures(world1.textures))
		printf("Parsed all textures !\n");
	return (0);
}
