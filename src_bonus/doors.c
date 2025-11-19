/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:22:44 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/19 13:59:53 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdlib.h>

int	get_door_state(t_data *data, int i, int j)
{
	int	idx;
	
	idx = 0;
	while (idx < data->door_count)
	{
		if (data->doors[idx].x == j && data->doors[idx].y == i)
			return (data->doors[idx].is_open);
		idx++;
	}
	return (-1);
}

t_door	*get_door_from_pos(t_data *data, int i, int j)
{
	int	idx;

	idx = 0;
	while (idx < data->door_count)
	{
		if (data->doors[idx].x == j && data->doors[idx].y == i)
			return (&data->doors[idx]);
		idx++;
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