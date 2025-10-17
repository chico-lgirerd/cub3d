/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:51:25 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/17 19:17:10 by tiaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_line
{
	int	tex_x;
	int	tex_y;
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_line;

typedef struct	s_raycasting
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
	int		side;
	t_line	line;
}	t_raycasting;

typedef struct	s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct	s_key
{
	int	key_forward;
	int	key_backward;
	int	key_left;
	int	key_right;
	int	key_turn_left;
	int	key_turn_right;
}	t_key;

typedef	struct	s_exec_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_width;
	int				win_height;
	int				map_width;
	int				map_height;
	int				minimap_width;
	int				minimap_height;
	int				**map;
	t_player		player;
	t_raycasting	raycasting;
	t_img			game_img;
	t_img			minimap_img;
	t_key			key;
}	t_exec_data;

void	init_map(t_exec_data *data);
void	init_player(t_player *player);
void	init_image(t_exec_data *data);

int 	perform_raycasting(t_exec_data *data);
void	update_player(t_exec_data *data);

void	draw_minimap(t_exec_data *data);
void	draw_simple_wall(t_exec_data *data, int x, int draw_start, int draw_end);
void	draw_ceiling_floor(t_exec_data *data, int x, int draw_start, int draw_end);
void	draw_map(t_exec_data *data, int x);

int		key_press(int keycode, t_exec_data *data);
int		key_release(int keycode, t_exec_data *data);

void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
int 	rgb_to_int(int r, int g, int b);

int		end_game(t_exec_data *data);
void draw_ray_minimap(t_exec_data *data);


#endif