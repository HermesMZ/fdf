/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:40:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/24 15:59:53 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project_ortho_top(t_mlx_data *data, t_point p)
{
	p.px = (int)(p.x * data->zoom + data->offset_x);
	p.py = (int)(p.y * data->zoom + data->offset_y);
	return (p);
}

t_point	project_ortho_front(t_mlx_data *data, t_point p)
{
	p.px = (int)(p.x * data->zoom + data->offset_x);
	p.py = (int)(-p.z * data->zoom * data->depth + data->offset_y);
	return (p);
}

t_point	project_ortho_side(t_mlx_data *data, t_point p)
{
	p.px = (int)(p.y * data->zoom + data->offset_x);
	p.py = (int)(-p.z * data->zoom * data->depth + data->offset_y);
	return (p);
}

void	rotate(t_mlx_data *data, t_point *p)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	p->z *= data->depth;
	prev_x = p->x - data->map->centre.x;
	prev_y = p->y - data->map->centre.y;
	prev_z = p->z;
	p->y = prev_y * cos(data->angle_x) - prev_z * sin(data->angle_x);
	p->z = prev_y * sin(data->angle_x) + prev_z * cos(data->angle_x);
	prev_y = p->y;
	prev_z = p->z;
	p->x = prev_x * cos(data->angle_y) + prev_z * sin(data->angle_y);
	p->z = -prev_x * sin(data->angle_y) + prev_z * cos(data->angle_y);
	prev_x = p->x;
	prev_z = p->z;
	p->x = prev_x * cos(data->angle_z) - prev_y * sin(data->angle_z);
	p->y = prev_x * sin(data->angle_z) + prev_y * cos(data->angle_z);
}

t_point	project_iso(t_mlx_data *data, t_point p)
{
	rotate(data, &p);
	p.px = (int)(p.x * data->zoom + data->offset_x);
	p.py = (int)(p.y * data->zoom + data->offset_y - (p.z * data->zoom));
	return (p);
}
