/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:37:25 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/16 13:39:06 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
