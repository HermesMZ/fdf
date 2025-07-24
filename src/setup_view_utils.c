/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_view_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:39:57 by zoum              #+#    #+#             */
/*   Updated: 2025/07/24 16:28:55 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_bounds(t_point p_transformed, t_bounds *bounds)
{
	if (!bounds->first_point_processed)
	{
		bounds->min_x = p_transformed.px;
		bounds->max_x = p_transformed.px;
		bounds->min_y = p_transformed.py;
		bounds->max_y = p_transformed.py;
		bounds->first_point_processed = 1;
	}
	else
	{
		if (p_transformed.px < bounds->min_x)
			bounds->min_x = p_transformed.px;
		else if (p_transformed.px > bounds->max_x)
			bounds->max_x = p_transformed.px;
		if (p_transformed.py < bounds->min_y)
			bounds->min_y = p_transformed.py;
		else if (p_transformed.py > bounds->max_y)
			bounds->max_y = p_transformed.py;
	}
}

void	find_projected_minmax(t_mlx_data *data, t_bounds *bounds)
{
	int					l;
	int					c;
	t_point				p_original;
	t_point				p_transformed;

	l = 0;
	while (l < data->map->lines)
	{
		c = 0;
		while (c < data->map->columns)
		{
			p_original.x = (double)c;
			p_original.y = (double)l;
			p_original.z = (double)data->map->points[l][c].z;
			p_transformed = project(data, p_original);
			update_bounds(p_transformed, bounds);
			c++;
		}
		l++;
	}
}

void	setup_ortho_top_view(t_mlx_data *data)
{
	data->offset_x = (data->width / 2.0) - (data->map->centre.x * data->zoom);
	data->offset_y = (data->height / 2.0) - (data->map->centre.y * data->zoom);
}

void	setup_ortho_front_view(t_mlx_data *data)
{
	double	z_center;

	z_center = (data->map->max_z + data->map->min_z) / 2.0;
	data->offset_x = (data->width / 2.0) - (data->map->centre.x * data->zoom);
	data->offset_y = (data->height / 2.0) + (z_center * data->zoom
			* data->depth);
}

void	setup_ortho_side_view(t_mlx_data *data)
{
	double	z_center;

	z_center = (data->map->max_z + data->map->min_z) / 2.0;
	data->offset_x = (data->width / 2.0) - (data->map->centre.y * data->zoom);
	data->offset_y = (data->height / 2.0) + (z_center * data->zoom
			* data->depth);
}
