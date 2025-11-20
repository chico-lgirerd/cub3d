/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:29:24 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/20 17:29:57 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	trim(char *str)
{
	int	start;
	int	end;
	int	i;
	int	j;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] && ft_isspace(str[start]))
		start++;
	while (end >= start && ft_isspace(str[end]))
		end--;
	if (start > 0)
	{
		i = start;
		j = 0;
		while (i <= end)
		{
			str[j] = str[i];
			i++;
			j++;
		}
		str[j] = '\0';
	}
	else
		str[end + 1] = '\0';
}

void	trim_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		trim(map[i]);
		i++;
	}
}

int	empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	put_spaces(char *dst, int *i)
{
	dst[(*i)++] = ' ';
	dst[(*i)++] = ' ';
	dst[(*i)++] = ' ';
	dst[(*i)++] = ' ';
}
