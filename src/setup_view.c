/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:12:49 by zoum              #+#    #+#             */
/*   Updated: 2025/07/19 01:47:17 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	calculate_initial_zoom(t_mlx_data *data, t_bounds *bounds)
{
	double	zoom;

	zoom = fmin((data->width * 0.8) / (double)(bounds->max_x - bounds->min_x),
			(data->height * 0.8) / (double)(bounds->max_y - bounds->min_y));
	return (zoom);
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

	z_size = data->map->max_z - data->map->min_z;
	if (z_size)
		data->depth = pow(z_size, -1);
	bounds = (t_bounds){0};
	find_projected_minmax(data, &bounds);
	data->zoom = calculate_initial_zoom(data, &bounds);
	find_projected_minmax(data, &bounds);
	calculate_and_set_offset(data, &bounds);
	printf("max %d min %d z_size %d depth %f zoom %f\n", data->map->max_z,
		data->map->min_z, 00000, data->depth, data->zoom);
}
