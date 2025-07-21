/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:59:59 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/21 13:50:06 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_handle_zoom_keys(t_mlx_data *data)
{
	if (data->keys.zoom_in)
	{
		if (data->zoom < 100)
			data->zoom += 0.01;
	}
	if (data->keys.zoom_out)
	{
		if (data->zoom > 1)
			data->zoom -= 0.01;
	}
	if (data->keys.depth_in)
	{
		if (data->depth < 5.0)
			data->depth += 0.001;
	}
	if (data->keys.depth_out)
	{
		if (data->depth > -5.0)
			data->depth -= 0.001;
	}
}

static void	_handle_move_keys(t_mlx_data *data)
{
	if (data->keys.angle_x_plus)
		data->angle_x += 0.001;
	if (data->keys.angle_x_minus)
		data->angle_x -= 0.001;
	if (data->keys.angle_y_plus)
		data->angle_y += 0.001;
	if (data->keys.angle_y_minus)
		data->angle_y -= 0.001;
	if (data->keys.angle_z_plus)
		data->angle_z += 0.001;
	if (data->keys.angle_z_minus)
		data->angle_z -= 0.001;
	if (data->keys.move_up)
		data->offset_y -= 1;
	if (data->keys.move_down)
		data->offset_y += 1;
	if (data->keys.move_left)
		data->offset_x -= 1;
	if (data->keys.move_right)
		data->offset_x += 1;
}

int	colorize(t_mlx_data *data)
{
	if (!data->colorized)
	{
		generate_gradient_palette(data);
		if (!data->palette.colors)
			return (1);
		update_colors(data);
		draw_map(data);
		free(data->palette.colors);
		data->colorized = 1;
	}
	return (0);
}

int	main_loop_update(t_mlx_data *data)
{
	t_keys	stop;

	stop = (t_keys){0};
	_handle_zoom_keys(data);
	_handle_move_keys(data);
	if (ft_memcmp(&data->keys, &stop, sizeof(t_keys)))
		draw_map(data);
	data->keys.first_draw = 0;
	return (0);
}
	// ft_printf("zoom %d\n", data->zoom);
