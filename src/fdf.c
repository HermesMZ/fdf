/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:09 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/20 17:39:38 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	launch(t_mlx_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
			"MY WORLD !");
	if (data->win_ptr == NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		return (1);
	}
	data->img->img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img->addr = mlx_get_data_addr(data->img->img,
			&data->img->bits_per_pixel, &data->img->line_len,
			&data->img->endian);
	draw_map(data);
	return (0);
}
