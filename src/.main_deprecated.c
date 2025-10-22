/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:57:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/22 15:38:09 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "mlx.h"
#include "exec.h"
#include <stdlib.h>
#include <stdio.h>

void	print_textures(t_textures textures)
{
	printf("North : %p\n", textures.north.img);
	printf("South : %p\n", textures.south.img);
	printf("West : %p\n", textures.west.img);
	printf("East : %p\n", textures.east.img);
	printf("Ceiling : %d, %d, %d\n", textures.ceiling.red, textures.ceiling.green, textures.ceiling.blue);
	printf("Floor : %d, %d, %d\n", textures.floor.red, textures.floor.green, textures.floor.blue);
}

int	main(int ac, char **av)
{
	t_world		*w;
	t_exec_data	*d;

	if (!check_args(ac, av))
		return (1);
	w = init_world();
	d = malloc(sizeof(t_exec_data));
	if (!d)
		return (1);
	ft_memset(d, 0, sizeof(t_exec_data));
	init_player(&d->player);
	if (!w || init_parsing(w, av[1]))
	{
		free_world(w);
		return (1);
	}
	if (have_textures(w->textures))
		printf("Parsed all textures\n");
	else
	{
		free_world(w);
		return (1);
	}
	if (!handle_map_error(is_valid_map(w->map, w->map_start)))
	printf("------- MAP IS VALID -------\n");
	print_textures(w->textures);
	free_world(w);
	return (0);
}
