/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:15:27 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/19 20:27:43 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_filename(char	*filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len <= 4)
		return (0);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
		return (0);
	return (1);
}

int	check_args(int ac, char **av)
{
	if (ac != 2 || !check_filename(av[1]))
	{
		ft_putstr_fd("Usage : ./cub3D <filename.cub>\n", 2);
		return (0);
	}
	return (1);
}
