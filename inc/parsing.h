/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:54:34 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/01 10:16:39 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_textures
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	t_color	floor;
	t_color	ceiling;
}	t_textures;

typedef struct s_player
{
	int	start_x;
	int	start_y;
}	t_player;

typedef struct s_world
{
	char		**map;
	t_textures	textures;
	t_player	player;
}	t_world;

char	**get_map(t_world *world, int fd, int lines);
int		check_args(int ac, char **av);

#endif