/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:12:56 by zoum              #+#    #+#             */
/*   Updated: 2025/07/16 22:31:53 by zoum             ###   ########.fr       */
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

static void	move_draw(t_draw *draw, t_point *p1)
{
	int	err;

	err = 2 * draw->err;
	if (err > -draw->dy)
	{
		draw->err -= draw->dy;
		p1->px += draw->sx;
	}
	if (err < draw->dx)
	{
		draw->err += draw->dx;
		p1->py += draw->sy;
	}
}

void	draw_line(t_point *p1, t_point p2, t_mlx_data *data, int color)
{
	t_draw	draw;

	draw.dx = abs(p2.px - p1->px);
	draw.dy = abs(p2.py - p1->py);
	if (p1->px < p2.px)
		draw.sx = 1;
	else
		draw.sx = -1;
	if (p1->py < p2.py)
		draw.sy = 1;
	else
		draw.sy = -1;
	draw.err = draw.dx - draw.dy;
	while (1)
	{
		my_mlx_pixel_put(data, p1->px, p1->py, color);
		if (p1->px == p2.px && p1->py == p2.py)
			break ;
		move_draw(&draw, p1);
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
			point.z = (double)data->map->points_map[l][c].z;
			point = rotate(data, point);
			point = project(data, point);
			my_mlx_pixel_put(data, point.px, point.py, 0xFFFFFF);
			link_points(data, c, l, &point);
			c++;
		}
		l++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img, 0, 0);
	draw_commands(data);
}
