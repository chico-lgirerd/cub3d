/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:40:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/16 13:38:22 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

int	is_map_char(char c, int *player_count)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player_count)++;
		return (1);
	}
	if (c == '0' || c == '1')
		return (1);
	if (ft_isspace(c))
		return (1);
	return (0);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_map(char **map, int start)
{
	int	player_count;
	int	rows;
	int	i;
	int	j;

	i = start - 1;
	rows = get_map_rows(map);
	player_count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_map_char(map[i][j], &player_count))
				return (3);
			if (player_count > 1)
				return (1);
			if (map[i][j] == '0' || is_player_char(map[i][j]))
				if (i == start || !check_surround(map, i, j, rows))
					return (2);
		}
	}
	if (player_count != 1)
		return (1);
	return (0);
}
