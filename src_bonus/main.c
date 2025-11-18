/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:46 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/18 13:01:11 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "mlx.h"

void	print_doors(t_data *data)
{
	#include <stdio.h>
	int	i = 0;
	while (i < data->door_count)
	{
		printf("%d, %d\n", data->doors[i].y, data->doors[i].x);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	data.doors = malloc(100 * sizeof(t_door));
	if (!data.doors)
		return (1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	if (init_map(&data, av[1]))
	{
		secure_free(&data);
		return (1);
	}
	print_doors(&data);
	init_player(&data.player);
	exec_game(&data);
	return (0);
}
