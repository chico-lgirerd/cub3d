/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:47:36 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/14 14:29:58 by lgirerd          ###   ########lyon.fr   */
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
		world->textures.north = mlx_xpm_file_to_image(world->mlx_ptr,
				*mapline, &world->textures.width, &world->textures.height);
	else if (!ft_strcmp(key, "SO"))
		world->textures.south = mlx_xpm_file_to_image(world->mlx_ptr,
				*mapline, &world->textures.width, &world->textures.height);
	else if (!ft_strcmp(key, "WE"))
		world->textures.west = mlx_xpm_file_to_image(world->mlx_ptr,
				*mapline, &world->textures.width, &world->textures.height);
	else if (!ft_strcmp(key, "EA"))
		world->textures.east = mlx_xpm_file_to_image(world->mlx_ptr,
				*mapline, &world->textures.width, &world->textures.height);
	else if ((key[0] == 'F' || key[0] == 'C') && (!key[1] || key[1] == ' '))
		fill_rgb(world, key, mapline);
	else
		return (1);
	return (0);
}

int	get_textures(t_world *world, char *mapline)
{
	char	key[3];

	skip_spaces(&mapline);
	if (!mapline[0] || !mapline[1])
		return (1);
	key[0] = *mapline;
	mapline++;
	key[1] = *mapline;
	mapline++;
	key[2] = '\0';
	trim(mapline);
	load_texture(world, key, &mapline);
	return (0);
}

int	have_textures(t_textures textures)
{
	if (!textures.east || !textures.north || !textures.south
		|| !textures.west)
		return (0);
	if (!valid_colors(textures))
		return (0);
	return (1);
}
