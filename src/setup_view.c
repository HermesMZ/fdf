/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:12:49 by zoum              #+#    #+#             */
/*   Updated: 2025/07/23 13:36:37 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	calculate_initial_zoom(t_mlx_data *data, t_bounds *bounds)
{
	double	sx;
	double	sy;

	sx = 0.0;
	sy = 0.0;
	while (sx < data->width * 0.9 && sy < data->height * 0.9)
	{
		find_projected_minmax(data, bounds);
		sx = bounds->max_x - bounds->min_x;
		sy = bounds->max_y - bounds->min_y;
		data->zoom += 0.01;
	}
}

static void	calculate_and_set_offset(t_mlx_data *data, t_bounds *bounds)
{
	double	center_x;
	double	center_y;

	center_x = (bounds->min_x + bounds->max_x) / 2.0;
	center_y = (bounds->min_y + bounds->max_y) / 2.0;
	data->offset_x = ((data->width / 2.0) - center_x);
	data->offset_y = ((data->height / 2.0) - center_y);
}

void	setup_view(t_mlx_data *data)
{
	t_bounds	bounds;
	int			z_size;

	z_size = data->map->max_z - (data->map->min_z);
	if (z_size)
		data->depth = pow(z_size, -0.5);
	bounds = (t_bounds){0};
	calculate_initial_zoom(data, &bounds);
	calculate_and_set_offset(data, &bounds);
}
