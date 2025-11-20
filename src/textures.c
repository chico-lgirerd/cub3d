/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:47:36 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/20 11:59:35 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <stdio.h>

void	skip_spaces(char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
}

int	fill_rgb(t_data *d, char *key, char **mapline)
{
	if (key[0] == 'F')
	{
		d->textures.floor.red = color_until_comma(mapline);
		d->textures.floor.green = color_until_comma(mapline);
		d->textures.floor.blue = color_until_comma(mapline);
		if (color_until_comma(mapline) != -1)
			return (0);
	}
	else if (key[0] == 'C')
	{
		d->textures.ceiling.red = color_until_comma(mapline);
		d->textures.ceiling.green = color_until_comma(mapline);
		d->textures.ceiling.blue = color_until_comma(mapline);
		if (color_until_comma(mapline) != -1)
			return (0);
	}
	return (1);
}

int	load_texture(t_data *data, char *key, char **mapline)
{
	if (!ft_strcmp(key, "NO"))
		load_north(data, *mapline);
	else if (!ft_strcmp(key, "SO"))
		load_south(data, *mapline);
	else if (!ft_strcmp(key, "WE"))
		load_west(data, *mapline);
	else if (!ft_strcmp(key, "EA"))
		load_east(data, *mapline);
	else if ((key[0] == 'F' || key[0] == 'C') && (!key[1] || key[1] == ' '))
	{
		if (!fill_rgb(data, key, mapline))
		{
			printf("Error\nToo much colors\n");
			return (0);
		}
	}
	else
	{
		printf("Error\nKey not recognized\n");
		return (0);
	}
	return (1);
}

int	get_textures(t_data *data, char *mapline)
{
	char	key[3];

	skip_spaces(&mapline);
	if (!mapline[0] || !mapline[1])
		return (0);
	key[0] = *mapline;
	mapline++;
	key[1] = *mapline;
	mapline++;
	key[2] = '\0';
	trim(mapline);
	if (!load_texture(data, key, &mapline))
		return (1);
	return (0);
}

int	have_textures(t_textures textures)
{
	if (!textures.east.loaded || !textures.north.loaded
		|| !textures.south.loaded || !textures.west.loaded)
	{
		printf("Error\nMissing texture, please check its path\n");
		return (0);
	}
	if (!textures.east.img || !textures.north.img
		|| !textures.south.img || !textures.west.img)
	{
		printf("Error\nMissing texture, please check its path\n");
		return (0);
	}
	if (!valid_colors(textures))
	{
		printf("Error\nInvalid color(s)\n");
		return (0);
	}
	return (1);
}
