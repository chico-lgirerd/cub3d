/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:46 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/19 20:18:48 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "mlx.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	if (init_map(&data, av[1]))
	{
		secure_free(&data);
		return (1);
	}
	init_player(&data.player);
	exec_game(&data);
	return (0);
}
