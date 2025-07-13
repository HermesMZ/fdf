/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:12:56 by zoum              #+#    #+#             */
/*   Updated: 2025/07/13 02:54:23 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_my_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->addr)) = color;
}

static t_point	rotate(t_mlx)

void	draw_map(t_mlx_data *data)
{
	int		l;
	int		c;
	t_point	point;

	ft_memset(data->img->addr, 0, data->width * data->height
		* (data->img->bits_per_pixel / 8));
	l = 0;
	while (l < data->map->lines)
	{
		c = 0;
		while (c < data->map->columns)
		{
			point.x = c;
			point.y = l;
			point.z = data->map->array_map[l][c];
			point = rotate(data, point);
			point = project(data, point);
			my_mlx_pixel_put(data->img, point.px, point.py, 0xFFFFFF);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img,
		0, 0);
}
