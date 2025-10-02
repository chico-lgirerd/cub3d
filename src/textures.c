/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:47:36 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/02 17:08:43 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "mlx.h"

void	skip_spaces(char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
	return (str);
}

int	fill_rgb(t_world *world, char *key, char *mapline)
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
}

int	load_texture(t_world *world, char *key, char **mapline)
{
	if (!ft_strcmp(key, "NO"))
		world->textures.north = mlx_xpm_file_to_image(world->mlx_ptr,
				*mapline, world->textures.width, world->textures.height);
	else if (!ft_strcmp(key, "SO"))
		world->textures.south = mlx_xpm_file_to_image(world->mlx_ptr,
				*mapline, world->textures.width, world->textures.height);
	else if (!ft_strcmp(key, "WE"))
		world->textures.west = mlx_xpm_file_to_image(world->mlx_ptr,
				*mapline, world->textures.width, world->textures.height);
	else if (!ft_strcmp(key, "EA"))
		world->textures.east = mlx_xpm_file_to_image(world->mlx_ptr,
				*mapline, world->textures.width, world->textures.height);
	else if ((key[0] == 'F' || key[0] == 'F') && !key[1]) // have to check for second character in case of CX/FX
		fill_rgb(world, key[0], mapline);
	else
		return (1); // Texture not recognized
	return (0);
}

int	get_textures(t_world *world, char *mapline)
{
	char	key[3];

	skip_spaces(&mapline);
	if (!*mapline || !*mapline + 1)
		return (1); // No key found!
	key[0] = *mapline;
	key[1] = *mapline + 1;
	key[2] = '\0';
	mapline += 2;
	skip_spaces(&mapline);
	load_texture(world, key, &mapline);
}
