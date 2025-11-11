/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:21:11 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/11 13:12:35 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"

void	init_pause(t_data *data)
{
	data->pause.width = 1920;
	data->pause.height = 1080;
	data->pause.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/pause.xpm",
			&data->pause.width, &data->pause.height);
}
