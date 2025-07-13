/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:05:08 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/13 04:45:24 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
// # include "mlx_int.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

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
	int			zoom;
	int			offset_x;
	int			offset_y;
	double		angle_x;
	double		angle_y;
	double		angle_z;
}	t_mlx_data;

// hooks
int			handle_input(int keysym, t_mlx_data *data);
int			end_display(t_mlx_data *data);

// map
int			check_extract_map(t_mlx_data *data, int fd);
void		free_map(int **tab);

// draw
void		my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
void		draw_map(t_mlx_data *data);
void		draw_line(t_point *p1, t_point p2, t_mlx_data *data, int color);

// init
t_mlx_data	*init_data(void);

// utils
void		print_map(t_mlx_data *data);

#endif /*FDF_H*/