/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:12:49 by zoum              #+#    #+#             */
/*   Updated: 2025/07/13 18:43:55 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	calculate_initial_zoom(t_mlx_data *data)
{
	double	zoom;

	zoom = fmin((data->width * 0.8) / (double)data->map->columns,
			(data->height * 0.8) / (double)data->map->lines);
	return (zoom);
}

static void	calculate_and_set_offset_x(t_mlx_data *data, double min_x,
	double max_x)
{
	data->offset_x = (int)((data->width / 2.0)
			- (min_x + ((max_x - min_x) / 2.0)));
}

static void	calculate_and_set_offset_y(t_mlx_data *data, double min_y,
	double max_y)
{
	data->offset_y = (int)((data->height / 2.0)
			- (min_y + ((max_y - min_y) / 2.0)));
}

void	setup_view(t_mlx_data *data)
{
	t_projected_bounds	bounds;

	bounds = (t_projected_bounds){0, 0, 0, 0, 0};
	data->zoom = calculate_initial_zoom(data);
	find_projected_minmax(data, &bounds);
	calculate_and_set_offset_x(data, bounds.min_x, bounds.max_x);
	calculate_and_set_offset_y(data, bounds.min_y, bounds.max_y);
}
