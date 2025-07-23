/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:27:15 by zoum              #+#    #+#             */
/*   Updated: 2025/07/23 13:33:54 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// rotate 3D centre
t_point	rotate(t_mlx_data *data, t_point p)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	p.z *= data->depth;
	prev_x = p.x - data->map->centre.x;
	prev_y = p.y - data->map->centre.y;
	prev_z = p.z - data->map->centre.z;
	p.y = prev_y * cos(data->angle_x) - prev_z * sin(data->angle_x);
	p.z = prev_y * sin(data->angle_x) + prev_z * cos(data->angle_x);
	prev_y = p.y;
	prev_z = p.z;
	p.x = prev_x * cos(data->angle_y) + prev_z * sin(data->angle_y);
	p.z = -prev_x * sin(data->angle_y) + prev_z * cos(data->angle_y);
	prev_x = p.x;
	prev_z = p.z;
	p.x = prev_x * cos(data->angle_z) - prev_y * sin(data->angle_z);
	p.y = prev_x * sin(data->angle_z) + prev_y * cos(data->angle_z);
	return (p);
}

t_point	project(t_mlx_data *data, t_point p)
{
	p.px = (int)(p.x * data->zoom + data->offset_x) + (int)data->map->centre.x;
	p.py = (int)(p.y * data->zoom + data->offset_y) + (int)data->map->centre.y
		- (p.z * data->zoom);
	return (p);
}

static void	_column(t_mlx_data *data, int c, int l, t_point *point)
{
	t_point	point_right;
	t_point	point_tmp;

	ft_memcpy(&point_tmp, point, sizeof(t_point));
	if (c < data->map->columns - 1)
	{
		point_right.x = (double)(c + 1);
		point_right.y = (double)l;
		point_right.z = (double)data->map->points[l][c + 1].z;
		point_right.color = data->map->points[l][c + 1].color;
		point_right = rotate(data, point_right);
		point_right = project(data, point_right);
		draw_line(data, &point_tmp, &point_right);
	}
}

static void	_line(t_mlx_data *data, int c, int l, t_point *point)
{
	t_point	point_down;
	t_point	point_tmp;

	ft_memcpy(&point_tmp, point, sizeof(t_point));
	if (l < data->map->lines - 1)
	{
		point_down.x = (double)c;
		point_down.y = (double)(l + 1);
		point_down.z = (double)data->map->points[l + 1][c].z;
		point_down.color = data->map->points[l + 1][c].color;
		point_down = rotate(data, point_down);
		point_down = project(data, point_down);
		draw_line(data, &point_tmp, &point_down);
	}
}

void	link_points(t_mlx_data *data, int c, int l, t_point *point)
{
	if (c < data->map->columns - 1)
		_column(data, c, l, point);
	if (l < data->map->lines - 1)
		_line(data, c, l, point);
}
