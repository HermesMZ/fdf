/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:09 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/24 19:09:02 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	launch(t_mlx_data *data)
{
	if (data->width && data->height)
		data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
			"MY WORLD !");
	if (data->win_ptr == NULL)
		return (end_display(data), 1);
	data->img->img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img->addr = mlx_get_data_addr(data->img->img,
			&data->img->bits_per_pixel, &data->img->line_len,
			&data->img->endian);
	draw_map(data);
	return (0);
}
