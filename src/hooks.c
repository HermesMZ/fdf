/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:59:59 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/24 16:27:14 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_handle_zoom_keys(t_mlx_data *data, int turbo)
{
	if (data->keys.zoom_in)
	{
		if (data->zoom < 100)
			data->zoom += 0.01 * turbo;
	}
	if (data->keys.zoom_out)
	{
		if (data->zoom > 1)
			data->zoom -= 0.01 * turbo;
	}
	if (data->keys.depth_in)
	{
		if (data->depth < 5.0)
		{
			data->depth += 0.001 * turbo;
		}
	}
	if (data->keys.depth_out)
	{
		if (data->depth > -5.0)
		{
			data->depth -= 0.001 * turbo;
		}
	}
}

static void	_handle_move_keys(t_mlx_data *data, int turbo)
{
	if (data->keys.angle_x_plus)
		data->angle_x += 0.001 * turbo;
	if (data->keys.angle_x_minus)
		data->angle_x -= 0.001 * turbo;
	if (data->keys.angle_y_plus)
		data->angle_y += 0.001 * turbo;
	if (data->keys.angle_y_minus)
		data->angle_y -= 0.001 * turbo;
	if (data->keys.angle_z_plus)
		data->angle_z += 0.001 * turbo;
	if (data->keys.angle_z_minus)
		data->angle_z -= 0.001 * turbo;
	if (data->keys.move_up)
		data->offset_y -= 1 * turbo;
	if (data->keys.move_down)
		data->offset_y += 1 * turbo;
	if (data->keys.move_left)
		data->offset_x -= 1 * turbo;
	if (data->keys.move_right)
		data->offset_x += 1 * turbo;
}

int	colorize(t_mlx_data *data)
{
	if (!data->colorized)
	{
		generate_gradient_palette(data);
		if (!data->palette.colors)
			return (1);
		draw_map(data);
		data->colorized = 1;
	}
	return (0);
}

int	main_loop_update(t_mlx_data *data)
{
	t_keys	stop;
	int		turbo;

	stop = (t_keys){0};
	turbo = 1;
	if (data->keys.turbo)
		turbo = 5;
	_handle_zoom_keys(data, turbo);
	_handle_move_keys(data, turbo);
	if (ft_memcmp(&data->keys, &stop, sizeof(t_keys)))
		draw_map(data);
	data->keys.first_draw = 0;
	return (0);
}
