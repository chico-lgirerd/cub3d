/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:40:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/08 15:31:58 by lgirerd          ###   ########lyon.fr   */
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

int	is_valid_map(t_world *world, char **map, int start)
{
	int	player_count;
	int	rows;
	int	cols;
	int	i;
	int	j;

	i = start;
	rows = get_map_rows(map);
	player_count = 0;
	while (i < rows)
	{
		cols = ft_strlen(map[i]);
		j = offset_spaces(map[i]);
		while (j < cols)
		{
			char	c = map[i][j];
			if (!c)
			{
				j++;
				continue ;
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				printf("\033[31;47m%c\033[0m", c);
				player_count++;
				world->player.start_x = i + start;
				world->player.start_y = j;
				j++;
				continue ;
			}
			if (player_count > 1)
			{
				printf("Too many players\n");
				return (0);
			}
			else if (c != '0' && c != '1' && c != ' ' && c != '\n')
			{
				printf("Unrecognized character at position %d, %d : \033[31;47m'%c'\033[0m", i + start + 1, j, c);
				j++;
				continue ;
			}
			if (c == '0')
			{
				if (i == start || j == 0 || i == rows - 1)
				{
					printf("\n0 on edge of map\n");
					return (0);
				}
				if (!map[i][j + 1] || map[i][j + 1] == '\n')
				{
					printf("\n0 on edge of map\n");
					return (0);
				}
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
				{
					printf("Hole in the map\n");
					return (0);
				}
			}
			printf("%c", c);
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		printf("No starting position found\n");
		return (0);
	}
	printf("\n");
	return (1);
}
