/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:54:34 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/16 13:38:09 by lgirerd          ###   ########lyon.fr   */
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
	int		width;
	int		height;
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
	void		*mlx_ptr;
	void		*win_ptr;
	t_textures	textures;
	t_player	player;
}	t_world;

int		check_args(int ac, char **av);
void	trim_map(char **map);
int		empty(char *str);
char	**map_from_file(char *filename, char **map);
int		color_until_comma(char **color);
int		get_textures(t_world *world, char *mapline);
void	skip_spaces(char **str);
int		valid_colors(t_textures textures);
int		have_textures(t_textures textures);
void	trim(char *str);
int		is_valid_map(char **map, int start);
void	print_textures(t_textures textures);
int		handle_map_error(int errcode);
int		check_surround(char **map, int i, int j, int rows);
int		check_below(char **map, int i, int j);
int		check_above(char **map, int i, int j);

#endif