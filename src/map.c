/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:40:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/07 17:46:55 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

int	get_map_rows(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	is_valid_map(char **map, int start)
{
	int	player_count;
	int rows = get_map_rows(map);
	int cols;
	int	i;
	int	j;

	i = start;
	player_count = 0;
	while (i < rows)
	{
		cols = ft_strlen(map[i]);
		j = 0;
		while (j < cols - 1)
		{
			char c = map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player_count++;
				j++;
				continue;
			}
			if (player_count > 1)
			{
				printf("Too many players\n");
				return (0);
			}
			else if (c != '0' && c != '1' && c != ' ')
			{
				printf("Unrecognized character at position %d, %d : '%c'\n", i, j, c);
				return (0);
			}
			if (c == '0')
			{
				if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1)
				{
					printf("0 on edge of map\n");
					return (0);
				}
				if (map[i - 1][j] == ' '|| map[i + 1][j] == ' ' || map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
				{
					printf("Hole in the map\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		printf("No starting position found\n");
		return (0);
	}
	return (1);
}