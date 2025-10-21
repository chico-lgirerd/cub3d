/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:11:51 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/21 15:39:46 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "mlx.h"

void	load_north(t_world *w, char *mapline)
{
	t_wall	*n;

	n = &w->textures.north;
	n->img = mlx_xpm_file_to_image(w->mlx_ptr,
			mapline, &w->textures.width, &w->textures.height);
	if (n->img)
		n->addr = mlx_get_data_addr(n->img,
				&n->bpp, &n->length, &n->endian);
	if (!n->img || !n->addr)
		n->loaded = 0;
	n->loaded = 1;
}

void	load_south(t_world *w, char *mapline)
{
	t_wall	*s;

	s = &w->textures.south;
	s->img = mlx_xpm_file_to_image(w->mlx_ptr,
			mapline, &w->textures.width, &w->textures.height);
	if (s->img)
		s->addr = mlx_get_data_addr(s->img,
				&s->bpp, &s->length, &s->endian);
	if (!s->img || !s->addr)
		s->loaded = 0;
	s->loaded = 1;
}

void	load_west(t_world *w, char *mapline)
{
	t_wall	*we;

	we = &w->textures.west;
	we->img = mlx_xpm_file_to_image(w->mlx_ptr,
			mapline, &w->textures.width, &w->textures.height);
	if (we->img)
		we->addr = mlx_get_data_addr(we->img,
				&we->bpp, &we->length, &we->endian);
	if (!we->img || !we->addr)
		we->loaded = 0;
	we->loaded = 1;
}

void	load_east(t_world *w, char *mapline)
{
	t_wall	*e;

	e = &w->textures.east;
	e->img = mlx_xpm_file_to_image(w->mlx_ptr,
			mapline, &w->textures.width, &w->textures.height);
	if (e->img)
		e->addr = mlx_get_data_addr(e->img,
				&e->bpp, &e->length, &e->endian);
	if (!e->img || !e->addr)
		e->loaded = 0;
	e->loaded = 1;
}
