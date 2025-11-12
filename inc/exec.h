/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:51:25 by tiaperei          #+#    #+#             */
/*   Updated: 2025/11/12 16:01:03 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parsing.h"
# include <sys/time.h>

# define BASE_SPEED 2.5
# define KEY_SENSI 1.5
# define MOUSE_SENSI 0.0015
# define MINIMAP_ZOOM 25
# define INTERACT_RADIUS 1.8

typedef struct s_player
{
	char	start_char;
	int		start_x;
	int		start_y;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_door
{
	double	pos;
	int		is_open;
	double	open_pos;
	double	width;
}	t_door;

typedef struct s_draw
{
	int		line_height;
	int		start;
	int		end;
	int		tex_x;
	int		tex_y;
	t_wall	wall_tex;
}	t_draw;

typedef struct s_raycasting
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	walldist_x; // dist ray travel for the 1st x_side case
	double	walldist_y;
	double	deltadist_x; // dist horizontal to next case
	double	deltadist_y; // dist vertical to next case
	double	perp_walldist;
	int		step_x;	//next step of DDA algo
	int		step_y;
	int		hit;
	int		side;
	int		is_door;
	t_door	door;
	t_draw	draw;
}	t_raycasting;

typedef struct s_minimap
{
	int	width;
	int	height;
	int	start_x;
	int	start_y;
	int	map_x;
	int	map_y;
	int	player_x;
	int	player_y;
}	t_minimap;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_key
{
	int	key_forward;
	int	key_backward;
	int	key_left;
	int	key_right;
	int	key_turn_left;
	int	key_turn_right;
	int	key_sprint;
	int	key_pause;
}	t_key;

typedef struct s_mouse
{
	int	last_x;
	int	center_x;
	int	center_y;
	int	square_radius;
	int	recentered;
	int	button_pressed;
}	t_mouse;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_width;
	int				win_height;
	int				map_width;
	int				map_height;
	int				map_start;
	int				map_end;
	char			**map;
	t_player		player;
	t_raycasting	raycasting;
	t_minimap		minimap;
	t_img			game_img;
	t_img			minimap_img;
	t_img			door_img;
	t_img			pickaxe;
	t_img			totem;
	t_img			pause;
	t_img			buffer;
	t_key			key;
	t_mouse			mouse;
	t_textures		textures;
}	t_data;

int		init_map(t_data *data, char *filename);
void	init_player(t_player *player);
void	init_image(t_data *data);
void	init_pickaxe(t_data *data);
void	init_totem(t_data *data);
void	init_pause(t_data *data);

void	exec_game(t_data *data);
int		perform_raycasting(t_data *data);
void	update_player(t_data *data, struct timeval curr_time,
			struct timeval last_time);

void	draw_minimap(t_data *data);
void	draw_map(t_data *data, int x);

void	move_forward(t_data *data, t_player *player, float speed);
void	move_backward(t_data *data, t_player *player, float speed);
void	move_left(t_data *data, t_player *player, float speed);
void	move_right(t_data *data, t_player *player, float speed);
void	turn_camera(t_player *player, double rot);
int		is_moving(t_data *data);

int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		get_texture_color(t_wall *texture, int tex_x, int tex_y);
void	draw_cases(t_data *data, int x, int y);
void	draw_empty_cases(t_data *data, int x, int y);
void	draw_player(t_data *data);

int		rgb_to_int(int r, int g, int b);
int		color_to_int(t_color color);

void	init_mouse(t_data *data);
int		mouse_handler(int x, int y, t_data *data);
int		mouse_button_handler(int button, int x, int y, t_data *data);

void	draw_crosshair(t_data *data);
void	animate_pickaxe(t_data *data, int base_x, int base_y);
void	animate_totem(t_data *data, int base_x, int base_y);

void	destroy_images(t_data *data, void *mlx_ptr, t_textures *txs);
int		secure_free(t_data *data);
void	free_map(char **map);

#endif