/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:33:15 by zoum              #+#    #+#             */
/*   Updated: 2025/07/21 14:17:07 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	extract_rgb(t_col *col, int c)
{
	col->color = c;
	col->t = (col->color >> 24) & 0xFF;
	col->r = (col->color >> 16) & 0xFF;
	col->g = (col->color >> 8) & 0xFF;
	col->b = (col->color & 0xFF);
}

int	interpolate_color(t_col c1, t_col c2, double ratio)
{
	t_col	inter;

	inter.r = (c1.r + (c2.r - c1.r) * ratio);
	inter.g = (c1.g + (c2.g - c1.g) * ratio);
	inter.b = (c1.b + (c2.b - c1.b) * ratio);
	inter.t = (c1.t + (c2.t - c1.t) * ratio);
	return (inter.t << 24 | inter.r << 16 | inter.g << 8 | inter.b);
}

void	fill_palette(t_mlx_data *data, int len)
{
	int		i;
	int		j;
	t_col	next;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		next = (t_col){0};
		while (j < len)
		{
			if (data->palette.colors[j].color)
			{
				next = data->palette.colors[j];
				break ;
			}
			j++;
		}
		if (data->palette.colors[i].color == 0x0)
		{
			data->palette.colors[i].color
				= interpolate_color(data->palette.colors[i - 1],
					next, 1.0 / (double)(j - i));
			extract_rgb(&data->palette.colors[i], data->palette.colors[i].color);
		}
		i++;
	}
}

void	setup_palette(t_mlx_data *data, int len)
{
	data->palette.colors[0] = (t_col){0, 148, 0, 211, 0x9400D3};
	data->palette.colors[len - 1] = (t_col){0, 255, 0, 0, 0xFF0000};
	if (len == 3)
		data->palette.colors[1] = (t_col){0, 0, 255, 0, 0x00FF00};
	if (len == 4)
	{
		data->palette.colors[1] = (t_col){0, 0, 0, 255, 0x0000FF};
		data->palette.colors[2] = (t_col){0, 255, 255, 0, 0xFFFF00};
	}
	if (len == 5)
	{
		data->palette.colors[1] = (t_col){0, 0, 0, 255, 0x0000FF};
		data->palette.colors[2] = (t_col){0, 0, 255, 0, 0x00FF00};
		data->palette.colors[3] = (t_col){0, 255, 255, 0, 0xFFFF00};
	}
	if (len >= 7)
	{
		data->palette.colors[len * 1 / 6] = (t_col){0, 75, 0, 130, 0x4B0082};
		data->palette.colors[len * 2 / 6] = (t_col){0, 0, 0, 255, 0x0000FF};
		data->palette.colors[len * 3 / 6] = (t_col){0, 0, 255, 0, 0x00FF00};
		data->palette.colors[len * 4 / 6] = (t_col){0, 255, 255, 0, 0xFFFF00};
		data->palette.colors[len * 5 / 6] = (t_col){0, 255, 127, 0, 0xFF7F00};
	}
}

void	generate_gradient_palette(t_mlx_data *data)
{
	int		len;
	int		i;
	int		first;

	len = 0;
	first = data->map->min_z;
	while (first++ <= data->map->max_z)
		len++;
	data->palette.len = len;
	data->palette.colors = malloc(sizeof(t_col) * (len + 1));
	if (!data->palette.colors)
		return ;
	i = 0;
	while (i < len - 1)
	{
		data->palette.colors[i] = (t_col){0};
		i++;
	}
	setup_palette(data, len);
	fill_palette(data, len);
	debug_palette(data);
}

void	update_colors(t_mlx_data *data)
{
	int		i;
	int		j;
	int		z;

	i = 0;
	while (i < data->map->lines)
	{
		j = 0;
		while (j < data->map->columns)
		{
			z = data->map->points[i][j].z;
			data->map->points[i][j].color = data->palette.colors[z
				+ abs(data->map->min_z)];
			j++;
		}
		i++;
	}
}
