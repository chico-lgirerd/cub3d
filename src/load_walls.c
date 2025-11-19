/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:11:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/19 20:18:28 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"

void	load_north(t_data *d, char *mapline)
{
	t_wall	*n;

	n = &d->textures.north;
	n->img = mlx_xpm_file_to_image(d->mlx_ptr,
			mapline, &d->textures.width, &d->textures.height);
	if (n->img)
		n->addr = mlx_get_data_addr(n->img,
				&n->bpp, &n->length, &n->endian);
	if (!n->img || !n->addr)
		n->loaded = 0;
	else
		n->loaded = 1;
}

void	load_south(t_data *d, char *mapline)
{
	t_wall	*s;

	s = &d->textures.south;
	s->img = mlx_xpm_file_to_image(d->mlx_ptr,
			mapline, &d->textures.width, &d->textures.height);
	if (s->img)
		s->addr = mlx_get_data_addr(s->img,
				&s->bpp, &s->length, &s->endian);
	if (!s->img || !s->addr)
		s->loaded = 0;
	else
		s->loaded = 1;
}

void	load_west(t_data *d, char *mapline)
{
	t_wall	*we;

	we = &d->textures.west;
	we->img = mlx_xpm_file_to_image(d->mlx_ptr,
			mapline, &d->textures.width, &d->textures.height);
	if (we->img)
		we->addr = mlx_get_data_addr(we->img,
				&we->bpp, &we->length, &we->endian);
	if (!we->img || !we->addr)
		we->loaded = 0;
	else
		we->loaded = 1;
}

void	load_east(t_data *d, char *mapline)
{
	t_wall	*e;

	e = &d->textures.east;
	e->img = mlx_xpm_file_to_image(d->mlx_ptr,
			mapline, &d->textures.width, &d->textures.height);
	if (e->img)
		e->addr = mlx_get_data_addr(e->img,
				&e->bpp, &e->length, &e->endian);
	if (!e->img || !e->addr)
		e->loaded = 0;
	else
		e->loaded = 1;
}
