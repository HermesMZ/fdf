/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:27:15 by zoum              #+#    #+#             */
/*   Updated: 2025/07/16 20:07:07 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	rotate(t_mlx_data *data, t_point p)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_x = p.x;
	prev_y = p.y;
	prev_z = p.z;
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
	p.px = (int)(p.x * data->zoom + data ->offset_x);
	p.py = (int)(p.y * data->zoom + data->offset_y
			- (p.z * data->zoom * data->depth));
	return (p);
}

void	link_points(t_mlx_data *data, int c, int l, t_point *point)
{
	t_point	point_right;
	t_point	point_down;
	t_point	point_tmp;

	ft_memcpy(&point_tmp, point, sizeof(t_point));
	if (c < data->map->columns - 1)
	{
		point_right.x = (double)(c + 1);
		point_right.y = (double)l;
		point_right.z = (double)data->map->array_map[l][c + 1];
		point_right = rotate(data, point_right);
		point_right = project(data, point_right);
		draw_line(&point_tmp, point_right, data, 0xFFFFFF);
	}
	ft_memcpy(&point_tmp, point, sizeof(t_point));
	if (l < data->map->lines - 1)
	{
		point_down.x = (double)c;
		point_down.y = (double)(l + 1);
		point_down.z = (double)data->map->array_map[l + 1][c];
		point_down = rotate(data, point_down);
		point_down = project(data, point_down);
		draw_line(&point_tmp, point_down, data, 0xFFFFFF);
	}
}


