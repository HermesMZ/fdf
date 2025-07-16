/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:44:35 by zoum              #+#    #+#             */
/*   Updated: 2025/07/16 20:47:51 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_commands_2(t_mlx_data *data, int x, int y, int line_height)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000,
		"MoveV: W (Up) / S (Down)");
	y += line_height;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000,
		"MoveH: A (Left) / D (Right)");
	y += line_height;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000,
		"Depth: Q (In) / E (Out)");
	y += line_height;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000,
		"Quit: ESC");
	y += line_height;
}

void	draw_commands(t_mlx_data *data)
{
	int	x;
	int	y;
	int	line_height;

	x = 20;
	y = 20;
	line_height = 20;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000,
		"--- FdF Commands ---");
	y += line_height;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000,
		"Zoom: H (In) / Y (Out)");
	y += line_height;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000,
		"Rot. X: U (+) / J (-)");
	y += line_height;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000,
		"Rot. Y: I (+) / K (-)");
	y += line_height;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000,
		"Rot. Z: O (+) / L (-)");
	y += line_height;
	draw_commands_2(data, x, y, line_height);
}
