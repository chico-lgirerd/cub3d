/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:57:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/19 18:13:02 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "mlx.h"
#include "libft.h"

#include <stdio.h>

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
	t_world	*w;

	w = malloc(sizeof(t_world));
	if (!w)
		return (1);
	ft_memset(w, 0, sizeof(t_world));
	if (!check_args(ac, av))
	{
		free(w);
		return (1);
	}
	if (init_world(w) || init_parsing(w, av[1]))
	{
		printf("Coucou\n");
		free_world(w);
		return (1);
	}
	printf("Coucou22222\n");
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
