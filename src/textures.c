/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:47:36 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/21 15:37:19 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "mlx.h"

#include <stdio.h>

void	skip_spaces(char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
}

int	fill_rgb(t_world *world, char *key, char **mapline)
{
	if (key[0] == 'F')
	{
		world->textures.floor.red = color_until_comma(mapline);
		world->textures.floor.green = color_until_comma(mapline);
		world->textures.floor.blue = color_until_comma(mapline);
	}
	else if (key[0] == 'C')
	{
		world->textures.ceiling.red = color_until_comma(mapline);
		world->textures.ceiling.green = color_until_comma(mapline);
		world->textures.ceiling.blue = color_until_comma(mapline);
	}
	if (!valid_colors(world->textures))
		return (0);
	return (1);
}

int	load_texture(t_world *world, char *key, char **mapline)
{
	if (!ft_strcmp(key, "NO"))
		load_north(world, *mapline);
	else if (!ft_strcmp(key, "SO"))
		load_south(world, *mapline);
	else if (!ft_strcmp(key, "WE"))
		load_west(world, *mapline);
	else if (!ft_strcmp(key, "EA"))
		load_east(world, *mapline);
	else if ((key[0] == 'F' || key[0] == 'C') && (!key[1] || key[1] == ' '))
		fill_rgb(world, key, mapline);
	else
	{
		printf("Error\nKey not recognized\n");
		return (0);
	}
	return (1);
}

int	get_textures(t_world *world, char *mapline)
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
	if (!load_texture(world, key, &mapline))
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
