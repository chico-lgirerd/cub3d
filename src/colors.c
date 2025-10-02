/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:45:36 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/02 17:47:15 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

int	color_until_comma(char **color)
{
	int	value;

	value = ft_atoi(*color);
	while (**color && (**color >= '0' && **color <= '9'))
		(*color)++;
	skip_spaces(color);
	if (**color == ',')
	{
		(*color)++;
		skip_spaces(color);
	}
	return (value);
}

int	valid_colors(t_textures textures)
{
	if (textures.ceiling.red < 0 || textures.ceiling.red > 255)
		return (0);
	else if (textures.ceiling.green < 0 || textures.ceiling.green > 255)
		return (0);	
	else if (textures.ceiling.blue < 0 || textures.ceiling.blue > 255)
		return (0);
	else if (textures.floor.red < 0 || textures.floor.red > 255)
		return (0);
	else if (textures.floor.green < 0 || textures.floor.green > 255)
		return (0);
	else if (textures.floor.blue < 0 || textures.floor.blue > 255)
		return (0);
	return (1);
}
