/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:57:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/02 17:51:47 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "mlx.h"

#include <stdio.h>

int	main(int ac, char **av)
{
	t_world	world1;
	char	**map;

	if (!check_args(ac, av))
		return (1);
	map = NULL;
	map = map_from_file(&world1, av[1], map);
	for (int i = 0; map[i]; i++)
		printf("%s", map[i]);
	printf("\n");
	world1.mlx_ptr = mlx_init();
	world1.win_ptr = mlx_new_window(world1.mlx_ptr, 800, 400, "test1");
	return (0);
}
