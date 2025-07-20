/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:33:15 by zoum              #+#    #+#             */
/*   Updated: 2025/07/20 20:33:11 by zoum             ###   ########.fr       */
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


unsigned int    *generate_gradient_palette(int z_min, int z_max)
{
	
}

void	update_colors(t_mlx_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < data->map->lines)
	{
		j = 0;
		while (j < data->map->columns)
		{
			extract_rgb(&data->map->points[i][j].color,
				get_gradient_color_for_z(data->map->points[i][j].z,
					data->map->min_z, data->map->max_z));
			j++;
		}
		i++;
	}
}
