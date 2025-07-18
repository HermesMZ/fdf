/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:59:59 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/18 16:14:12 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_handle_zoom_keys(t_mlx_data *data)
{
	if (data->keys.zoom_in)
	{
		if (data->zoom < 100)
			data->zoom += 1;
	}
	if (data->keys.zoom_out)
	{
		if (data->zoom > -100)
			data->zoom -= 1;
	}
	if (data->keys.depth_in)
	{
		if (data->depth < 2.0)
			data->depth += 0.01;
	}
	if (data->keys.depth_out)
	{
		if (data->depth > -2.0)
			data->depth -= 0.01;
	}
}

static void	_handle_move_keys(t_mlx_data *data)
{
	if (data->keys.angle_x_plus)
		data->angle_x += 0.01;
	if (data->keys.angle_x_minus)
		data->angle_x -= 0.01;
	if (data->keys.angle_y_plus)
		data->angle_y += 0.01;
	if (data->keys.angle_y_minus)
		data->angle_y -= 0.01;
	if (data->keys.angle_z_plus)
		data->angle_z += 0.01;
	if (data->keys.angle_z_minus)
		data->angle_z -= 0.01;
	if (data->keys.move_up)
		data->offset_y -= 10;
	if (data->keys.move_down)
		data->offset_y += 10;
	if (data->keys.move_left)
		data->offset_x -= 10;
	if (data->keys.move_right)
		data->offset_x += 10;
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
