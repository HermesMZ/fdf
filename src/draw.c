/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:12:56 by zoum              #+#    #+#             */
/*   Updated: 2025/07/19 01:24:46 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	offset = (data->img->line_len * y) + (x * (data->img->bits_per_pixel / 8));
	*((unsigned int *)(offset + data->img->addr)) = color;
}

static void	move_draw(t_draw *draw, int *current_x, int *current_y)
{
	int	err_check;

	err_check = 2 * draw->err;
	if (err_check > -draw->dy)
	{
		draw->err -= draw->dy;
		*current_x += draw->sx;
	}
	if (err_check < draw->dx)
	{
		draw->err += draw->dx;
		*current_y += draw->sy;
	}
}

void	draw_line(t_mlx_data *data, t_point *p1, t_point *p2)
{
	t_draw			draw;
	unsigned int	color;
	double			ratio;
	double			total_steps;
	int				step_count;

	draw.current_x = p1->px;
	draw.current_y = p1->py;
	draw.dx = abs(p2->px - p1->px);
	draw.dy = abs(p2->py - p1->py);
	if (p1->px < p2->px)
		draw.sx = 1;
	else
		draw.sx = -1;
	if (p1->py < p2->py)
		draw.sy = 1;
	else
		draw.sy = -1;
	draw.err = draw.dx - draw.dy;
	total_steps = sqrt(pow(draw.dx, 2) + pow(draw.dy, 2));
	step_count = 0;
	while (1)
	{
		ratio = (double)step_count / total_steps;
		color = interpolate_color(p1->color, p2->color, ratio);
		my_mlx_pixel_put(data, draw.current_x, draw.current_y, color);
		if (draw.current_x == p2->px && draw.current_y == p2->py)
			break ;
		move_draw(&draw, &draw.current_x, &draw.current_y);
		step_count++;
	}
}

void	draw_map(t_mlx_data *data)
{
	int		l;
	int		c;
	t_point	point;

	ft_memset(data->img->addr, 0, data->img->line_len * data->height);
	l = 0;
	while (l < data->map->lines)
	{
		c = 0;
		while (c < data->map->columns)
		{
			point.x = (double)c;
			point.y = (double)l;
			point.z = (double)data->map->points[l][c].z;
			point.color = data->map->points[l][c].color;
			point = rotate(data, point);
			point = project(data, point);
			my_mlx_pixel_put(data, point.px, point.py, point.color.color);
			link_points(data, c, l, &point);
			c++;
		}
		l++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img, 0, 0);
	draw_commands(data);
	printf("offset x %f offset y %f\n", data->offset_x, data->offset_y);
	printf("x %f y %f z %f\n", data->angle_x, data->angle_y, data->angle_z);
	printf("depth %f zoom %f\n\n", data->depth, data->zoom);
}
