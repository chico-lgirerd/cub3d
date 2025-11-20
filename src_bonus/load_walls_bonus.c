/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:11:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/11/20 13:22:08 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "mlx.h"

void	load_north(t_data *d, char *mapline)
{
	t_wall	*n;

	n = &d->textures.north;
	if (n->img)
		return ;
	n->img = mlx_xpm_file_to_image(d->mlx_ptr,
			mapline, &d->textures.width, &d->textures.height);
	if (n->img)
		n->addr = mlx_get_data_addr(n->img,
				&n->bpp, &n->length, &n->endian);
	if (!n->img || !n->addr)
		n->loaded = 0;
	n->loaded = 1;
}

void	load_south(t_data *d, char *mapline)
{
	t_wall	*s;

	s = &d->textures.south;
	if (s->img)
		return ;
	s->img = mlx_xpm_file_to_image(d->mlx_ptr,
			mapline, &d->textures.width, &d->textures.height);
	if (s->img)
		s->addr = mlx_get_data_addr(s->img,
				&s->bpp, &s->length, &s->endian);
	if (!s->img || !s->addr)
		s->loaded = 0;
	s->loaded = 1;
}

void	load_west(t_data *d, char *mapline)
{
	t_wall	*we;

	we = &d->textures.west;
	if (we->img)
		return ;
	we->img = mlx_xpm_file_to_image(d->mlx_ptr,
			mapline, &d->textures.width, &d->textures.height);
	if (we->img)
		we->addr = mlx_get_data_addr(we->img,
				&we->bpp, &we->length, &we->endian);
	if (!we->img || !we->addr)
		we->loaded = 0;
	we->loaded = 1;
}

void	load_east(t_data *d, char *mapline)
{
	t_wall	*e;

	e = &d->textures.east;
	if (e->img)
		return ;
	e->img = mlx_xpm_file_to_image(d->mlx_ptr,
			mapline, &d->textures.width, &d->textures.height);
	if (e->img)
		e->addr = mlx_get_data_addr(e->img,
				&e->bpp, &e->length, &e->endian);
	if (!e->img || !e->addr)
		e->loaded = 0;
	e->loaded = 1;
}

void	load_door(t_data *d, char *mapline)
{
	t_wall	*door;

	door = &d->textures.door;
	if (door->img)
		return ;
	door->img = mlx_xpm_file_to_image(d->mlx_ptr,
			mapline, &door->width, &door->height);
	if (door->img)
		door->addr = mlx_get_data_addr(door->img,
				&door->bpp, &door->length, &door->endian);
	if (!door->img || !door->addr)
		door->loaded = 0;
	else
		door->loaded = 1;
}
