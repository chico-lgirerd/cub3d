/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:57:00 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/02 17:04:00 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

	return (0);
}
