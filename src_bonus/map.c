/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:40:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/19 11:52:03 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec.h"
#include "parsing.h"

int	get_map_rows(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	offset_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int	is_map_char(t_data *data, int i, int j, int *player_count)
{
	if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
	{
		(*player_count)++;
		return (1);
	}
	if (data->map[i][j] == '0' || data->map[i][j] == '1')
		return (1);
	if (data->map[i][j] == 'D')
	{
		data->doors[data->door_count].x = j;
		data->doors[data->door_count].y = i - data->map_start + 1;
		data->doors[data->door_count].is_open = 0;
		data->doors[data->door_count].open_pos = 0.0;
		data->doors[data->door_count].width = 0.06;
		data->door_count++;
		return (1);
	}
	if (ft_isspace(data->map[i][j]))
		return (1);
	return (0);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_map(t_data *data, char **map, int start)
{
	int	player_count;
	int	i;
	int	j;

	i = start - 1;
	data->map_height = get_map_rows(map);
	player_count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_map_char(data, i, j, &player_count))
				return (3);
			if (player_count > 1)
				return (1);
			if (map[i][j] == '0' || is_player_char(map[i][j]))
				if (i == start || !check_surround(data, map, i, j))
					return (2);
		}
	}
	data->map_end = i;
	if (player_count != 1)
		return (1);
	return (0);
}
