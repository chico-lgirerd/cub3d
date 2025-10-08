/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:51:25 by tiaperei          #+#    #+#             */
/*   Updated: 2025/10/08 19:45:17 by tiaperei         ###   ########.fr       */
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

typedef struct s_raycasting
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	int		walldist_x; // dist ray travel for the 1st x_side case
	int		walldist_y;
	double	deltadist_x; // dist horizontal to next case
	double	deltadist_y; // dist vertical to next case
	double	perp_walldist;
	int		step_x;	//next step of DDA algo
	int		step_y;
	int		side;
	t_line	line;
}	t_raycasting;

typedef struct s_exec_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_width;
	int			win_height;
	int			map_width;
	int			map_height;
	int			**map;
	t_player	player;
	t_raycasting	raycasting;
}	t_exec_data;


int	end_game(t_exec_data *data);

#endif