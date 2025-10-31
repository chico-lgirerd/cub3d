/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:54:34 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/31 12:01:30 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_data t_data;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_wall
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
	int		loaded;
}	t_wall;

typedef struct s_textures
{
	int		width;
	int		height;
	t_wall	north;
	t_wall	south;
	t_wall	east;
	t_wall	west;
	t_color	floor;
	t_color	ceiling;
}	t_textures;

typedef struct s_world
{
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	int			map_start;
	t_textures	textures;
}	t_world;

int		check_args(int ac, char **av);
void	trim_map(char **map);
int		empty(char *str);
char	**map_from_file(char *filename);
int		color_until_comma(char **color);
int		get_textures(t_data *data, char *mapline);
void	skip_spaces(char **str);
int		valid_colors(t_textures textures);
int		have_textures(t_textures textures);
void	trim(char *str);
int		is_valid_map(t_data *data, char **map, int start);
void	print_textures(t_textures textures);
int		handle_map_error(int errcode);
int		check_surround(t_data *data, char **map, int i, int j);
int		check_below(char **map, int i, int j);
int		check_above(char **map, int i, int j);
int		is_map_line(char *line);
int		is_player_char(char c);

void	load_north(t_data *d, char *mapline);
void	load_south(t_data *d, char *mapline);
void	load_west(t_data *d, char *mapline);
void	load_east(t_data *d, char *mapline);

t_world	*init_world(void);
int		init_parsing(t_world *world, char *filename);
void	init_colors(t_color *ceiling, t_color *floor);

void	free_map(char **map);
void	free_world(t_world *world);

#endif