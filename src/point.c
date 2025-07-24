/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:27:15 by zoum              #+#    #+#             */
/*   Updated: 2025/07/24 15:14:13 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project(t_mlx_data *data, t_point p)
{
	if (data->keys.view == 1)
		return (project_ortho_top(data, p));
	else if (data->keys.view == 2)
		return (project_ortho_front(data, p));
	else if (data->keys.view == 3)
		return (project_ortho_side(data, p));
	else if (data->keys.view == 4)
		return (project_iso(data, p));
	else
		return (project_iso(data, p));
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
