/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:33:39 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/15 14:24:54 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	handle_map_error(int errcode)
{
	if (errcode == 1)
		printf("Error\nMap has to contain exactly one player position\n");
	else if (errcode == 2)
		printf("Error\nHole in the map\n");
	else if (errcode == 3)
		printf("Error\nUnknown character in the map\n");
	return (1);
}
