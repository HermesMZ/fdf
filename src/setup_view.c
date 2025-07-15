/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:12:49 by zoum              #+#    #+#             */
/*   Updated: 2025/07/15 14:37:21 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	calculate_initial_zoom(t_mlx_data *data, t_bounds *bounds)
{
	double	zoom;

	zoom = fmin((data->width * 0.9) / (double)(bounds->max_x - bounds->min_x),
			(data->height * 0.9) / (double)(bounds->max_y - bounds->min_y));

	return (zoom);
}

static void	calculate_and_set_offset(t_mlx_data *data, t_bounds *bounds)
{
	data->offset_x = (int)((data->width / 2.0)
			- ft_abs((bounds->min_x + ((bounds->max_x
							- bounds->min_x) / 2.0))));
	data->offset_y = (int)((data->height / 2.0)
			- ft_abs((bounds->max_y + ((bounds->min_y
							- bounds->max_y) / 2.0))));
}

void	setup_view(t_mlx_data *data)
{
	t_bounds	bounds;

	bounds = (t_bounds){0};
	find_projected_minmax(data, &bounds);
	data->zoom = calculate_initial_zoom(data, &bounds);
	find_projected_minmax(data, &bounds);
	calculate_and_set_offset(data, &bounds);
}
