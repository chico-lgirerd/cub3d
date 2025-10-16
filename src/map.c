/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:40:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/16 11:55:10 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

#include <stdio.h>

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
	return (c == '0' || c == '1');
}

int	check_above(char **map, int i, int j)
{
	int	above_cols;

	above_cols = ft_strlen(map[i - 1]);
	if (j >= above_cols - 1 || map[i - 1][j] == ' ' || map[i - 1][j] == '\n')
		return (0);
	return (1);
}

int	check_below(char **map, int i, int j)
{
	int	below_cols;

	below_cols = ft_strlen(map[i + 1]);
	if (j >= below_cols - 1 || map[i + 1][j] == ' ' || map[i + 1][j] == '\n')
		return (0);
	return (1);
}

int	check_surround(char **map, int i, int j, int rows)
{
	if (j == 0)
		return (0);
	if (!map[i][j + 1] || map[i][j + 1] == '\n')
		return (0);
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (0);
	if (i > 0 && !check_above(map, i, j))
		return (0);
	if (i < rows - 1 && !check_below(map, i, j))
		return (0);
	return (1);
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
			if (!is_map_char(map[i][j], &player_count) && !ft_isspace(map[i][j]))
				return (3);
			if (player_count > 1)
				return (1);
			if (map[i][j] == '0' || is_player_char(map[i][j]))
				if (i == start || i == rows - 1 || !check_surround(map, i, j, rows))
					return (2);
		}
	}
	if (player_count != 1)
		return (1);
	return (0);
}
