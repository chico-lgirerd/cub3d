/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:22:44 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/18 14:53:01 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdlib.h>

int	get_door_state(t_data *data, int x, int y)
{
	int	i;
	
	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (data->doors[i].is_open);
		i++;
	}
	return (-1);
}

t_door	*get_door_from_pos(t_data *data, int x, int y)
{
	int	i;

	// #include <stdio.h>
	// printf("Searching for : %d, %d\n", x, y);
	// printf("Door Count : %d\n", data->door_count);
	i = 0;
	while (i < data->door_count)
	{
		// printf("my x : %d door[%d] x : %d my y : %d door[%d] y : %d\n", x, i, data->doors[i].x, y, i, data->doors[i].y);
		if (data->doors[i].x == y && data->doors[i].y == x)
		{
			// printf("Returning %p\n", &data->doors[i]);
			return (&data->doors[i]);
		}
		i++;
	}
	return (NULL);
}

void	init_doors_pos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->door_count)
	{
		data->doors[i].open_pos = 0.0;
		data->doors[i].width = 0.06;
		i++;
	}
}