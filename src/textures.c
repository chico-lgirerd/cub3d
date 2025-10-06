/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:47:36 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/06 22:03:29 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "mlx.h"

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

#include <stdio.h>
#include <fcntl.h>

int	load_texture(t_world *world, char *key, char **mapline)
{
	printf("----- LOAD TEXTURES ----- \n");
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
	else if ((key[0] == 'F' || key[0] == 'C') && (!key[1] || key[1] == ' ')) // have to check for second character in case of CX/FX
		fill_rgb(world, key, mapline);
	else
	{
		printf("Key not recognized : \"%s\"\n", key);
		return (1); // Texture not recognized
	}
	printf("---- OUT OF LOAD ---- \n");
	return (0);
}

int	get_textures(t_world *world, char *mapline)
{
	char	key[3];
	printf("------- GET TEXTURES ------- \n");
	skip_spaces(&mapline);
	// if (!*mapline || !*mapline + 1)
		// return (1); // No key found!
	key[0] = *mapline;
	mapline++;
	key[1] = *mapline;
	mapline++;
	key[2] = '\0';
	trim(mapline);
	// mapline += 3;
	// skip_spaces(&mapline);
	load_texture(world, key, &mapline);
	return (0);
}


int	have_textures(t_textures textures)
{
	if (!textures.east || !textures.north || !textures.south
		|| !textures.west)
		return (0);
	printf("Have images\n");
	if (!valid_colors(textures))
		return (0);
	printf("Have colors\n");
	return (1);
}