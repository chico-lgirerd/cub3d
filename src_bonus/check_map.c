/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:37:25 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/19 20:14:27 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec.h"

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

int	check_surround(t_data *data, char **map, int i, int j)
{
	int	rows;

	rows = data->map_height;
	if (j > data->map_width)
		data->map_width = j;
	if (is_player_char(map[i][j]))
	{
		data->player.start_x = j;
		data->player.start_y = i;
		data->player.start_char = map[i][j];
		map[i][j] = '0';
	}
	if (i == rows - 1)
		return (0);
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
