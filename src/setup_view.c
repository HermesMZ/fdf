/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:12:49 by zoum              #+#    #+#             */
/*   Updated: 2025/07/14 16:05:45 by zoum             ###   ########.fr       */
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

// void	setup_view(t_mlx_data *data)
// {
// 	t_bounds	bounds;

// 	bounds = (t_bounds){0, 0, 0, 0, 0};
// 	data->zoom = calculate_initial_zoom(data);
// 	find_projected_minmax(data, &bounds);
// 	calculate_and_set_offset_x(data, bounds.min_x, bounds.max_x);
// 	calculate_and_set_offset_y(data, bounds.min_y, bounds.max_y);
// 	ft_printf("zoom : %d offx : %d offy : %d\n", data->zoom, data->offset_x, data->offset_y);
// 	// data->zoom = 23;
// 	// data->offset_x = 234;
// 	// data->offset_y = 160;
// }

void    setup_view(t_mlx_data *data)
{
	t_bounds  bounds = {0};

	find_projected_minmax(data, &bounds);
	
	// --- Ajoutez ces lignes pour le débogage ---
	printf("DEBUG: bounds.min_x = %f, bounds.max_x = %f\n", bounds.min_x, bounds.max_x);
	printf("DEBUG: bounds.min_y = %f, bounds.max_y = %f\n", bounds.min_y, bounds.max_y);
	printf("DEBUG: map_lines = %d, map_columns = %d\n", data->map->lines, data->map->columns);
	// --- Fin du débogage ---
	
	calculate_and_set_offset_x(data, bounds.min_x, bounds.max_x);
	calculate_and_set_offset_y(data, bounds.min_y, bounds.max_y);
	data->zoom = calculate_initial_zoom(data, &bounds);
	printf("DEBUG: Final offset_x = %d, offset_y = %d\n", data->offset_x, data->offset_y);
	printf("DEBUG: Final zoom = %d\n", data->zoom);
}