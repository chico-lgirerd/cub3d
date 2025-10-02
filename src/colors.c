/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:45:36 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/02 17:03:18 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
