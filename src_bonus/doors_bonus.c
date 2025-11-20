/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:22:44 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/19 20:27:04 by tiaperei         ###   ########.fr       */
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
