/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:06:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/21 16:46:39 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_find_next_color(t_mlx_data *data, int len, int *j, t_col *next)
{
	while (*j < len)
	{
		if (data->palette.colors[*j].color)
			*next = data->palette.colors[*j];
		(*j)++;
	}
}

static void	fill_palette(t_mlx_data *data, int len)
{
	int		i;
	int		j;
	t_col	next;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		_find_next_color(data, len, &j, &next);
		if (data->palette.colors[i].color == 0x0)
		{
			data->palette.colors[i].color
				= interpolate_color(data->palette.colors[i - 1],
					next, 1.0 / (double)(j - i));
			extract_rgb(&data->palette.colors[i],
				data->palette.colors[i].color);
		}
		i++;
	}
}

static void	update_colors(t_mlx_data *data)
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

static void	setup_palette(t_mlx_data *data, int len)
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
	update_colors(data);
	free(data->palette.colors);
}
