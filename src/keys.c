/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:55:34 by zoum              #+#    #+#             */
/*   Updated: 2025/07/24 16:00:06 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_press_views(int keysym, t_mlx_data *data)
{
	t_bounds	bounds;

	if (keysym == 122)
	{
		data->keys.view = 1;
		setup_ortho_top_view(data);
	}
	if (keysym == 120)
	{
		data->keys.view = 2;
		setup_ortho_front_view(data);
	}
	if (keysym == 99)
	{
		data->keys.view = 3;
		setup_ortho_side_view(data);
	}
	if (keysym == 118)
	{
		bounds = (t_bounds){0};
		calculate_and_set_offset(data, &bounds);
		data->keys.view = 4;
	}
	return (0);
}

static int	key_press_2(int keysym, t_mlx_data *data)
{
	if (keysym == 119)
		data->keys.move_up = 1;
	if (keysym == 115)
		data->keys.move_down = 1;
	if (keysym == 97)
		data->keys.move_left = 1;
	if (keysym == 100)
		data->keys.move_right = 1;
	if (keysym == 113)
		data->keys.depth_in = 1;
	if (keysym == 101)
		data->keys.depth_out = 1;
	if (keysym == 65505)
		data->keys.turbo = 1;
	return (0);
}

int	key_press(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		end_display(data);
	if (keysym == 32)
		colorize(data);
	if (keysym == 121)
		data->keys.zoom_out = 1;
	if (keysym == 104)
		data->keys.zoom_in = 1;
	if (keysym == 117)
		data->keys.angle_x_plus = 1;
	if (keysym == 106)
		data->keys.angle_x_minus = 1;
	if (keysym == 105)
		data->keys.angle_y_plus = 1;
	if (keysym == 107)
		data->keys.angle_y_minus = 1;
	if (keysym == 111)
		data->keys.angle_z_plus = 1;
	if (keysym == 108)
		data->keys.angle_z_minus = 1;
	key_press_2(keysym, data);
	key_press_views(keysym, data);
	return (0);
}

static int	key_release_2(int keysym, t_mlx_data *data)
{
	if (keysym == 119)
		data->keys.move_up = 0;
	if (keysym == 115)
		data->keys.move_down = 0;
	if (keysym == 97)
		data->keys.move_left = 0;
	if (keysym == 100)
		data->keys.move_right = 0;
	if (keysym == 113)
		data->keys.depth_in = 0;
	if (keysym == 101)
		data->keys.depth_out = 0;
	if (keysym == 65505)
		data->keys.turbo = 0;
	if (keysym == 118)
		data->keys.view = 0;
	return (0);
}

int	key_release(int keysym, t_mlx_data *data)
{
	if (keysym == 121)
		data->keys.zoom_out = 0;
	if (keysym == 104)
		data->keys.zoom_in = 0;
	if (keysym == 117)
		data->keys.angle_x_plus = 0;
	if (keysym == 106)
		data->keys.angle_x_minus = 0;
	if (keysym == 105)
		data->keys.angle_y_plus = 0;
	if (keysym == 107)
		data->keys.angle_y_minus = 0;
	if (keysym == 111)
		data->keys.angle_z_plus = 0;
	if (keysym == 108)
		data->keys.angle_z_minus = 0;
	key_release_2(keysym, data);
	return (0);
}
