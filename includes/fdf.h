/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:05:08 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/15 15:43:19 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
// # include "mlx_int.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <x86_64-linux-gnu/bits/fcntl-linux.h>
# include "libft.h"

typedef struct s_keys
{
	int	angle_x_plus;
	int	angle_x_minus;
	int	angle_y_plus;
	int	angle_y_minus;
	int	angle_z_plus;
	int	angle_z_minus;
	int	zoom_in;
	int	zoom_out;
	int	move_up;
	int	move_down;
	int	move_left;
	int	move_right;
	int	depth_in;
	int	depth_out;
}	t_keys;

typedef struct s_bounds
{
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
	int		first_point_processed;
}	t_bounds;

typedef struct s_draw
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_draw;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		px;
	int		py;
}	t_point;

typedef struct s_map
{
	int	lines;
	int	columns;
	int	**array_map;
}	t_map;

typedef struct s_my_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_my_img;

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	int			width;
	int			height;
	void		*win_ptr;
	t_map		*map;
	t_my_img	*img;
	t_keys		keys;
	int			zoom;
	int			offset_x;
	int			offset_y;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	double		depth;
}	t_mlx_data;

// hooks
int			handle_input(int keysym, t_mlx_data *data);
int			end_display(t_mlx_data *data);

// map
int			check_extract_map(t_mlx_data *data, char *file_path);

// draw
void		draw_map(t_mlx_data *data);
// void		my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
void		draw_line(t_point *p1, t_point p2, t_mlx_data *data, int color);

// point
void		link_points(t_mlx_data *data, int c, int l, t_point *point);
t_point		project(t_mlx_data *data, t_point p);
t_point		rotate(t_mlx_data *data, t_point p);


// init
t_mlx_data	*init_data(void);
int			**create_map(int lines, int col);
void		setup_view(t_mlx_data *data);

// utils
void		print_map(t_mlx_data *data);
void		free_map(int **tab);
void		close_gnl_fd(int fd);


// count
int			count_map_dimensions(t_mlx_data *data, char *file_path);
char		*new_line(int fd);

// setup
void		find_projected_minmax(t_mlx_data *data, t_bounds *bounds);


#endif /*FDF_H*/